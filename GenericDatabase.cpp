/*
 * Copyright © 2014 Volker Knollmann
 * 
 * This work is free. You can redistribute it and/or modify it under the
 * terms of the Do What The Fuck You Want To Public License, Version 2,
 * as published by Sam Hocevar. See the COPYING file or visit
 * http://www.wtfpl.net/ for more details.
 * 
 * This program comes without any warranty. Use it at your own risk or
 * don't use it at all.
 */

#include "GenericDatabase.h"
#include "HelperFunc.h"
#include "DbTab.h"
#include <stdexcept>
#include <iostream>
#include <cassert>

#include <QtCore>
#include <QFile>
#include <QtSql>
#include <QtSql/QSqlError>

using namespace std;

namespace dbOverlay
{
  int GenericDatabase::connectionCounter = 0;
  const int GenericDatabase::MYSQL_DEFAULT_PORT = 3306;

  /**
   * Creates a new database instance and connects to the DBMS
   * 
   * @param t the database engine type
   * @param srv the name of the database server or null for DBMS-specific default; for SQLITE, this is the path to the SQLite files
   * @param port the port of the database server to connect to or 0 for DBMS-specific default; special values for SQLite to indicate creating of a new file vs. opening of an existing
   * @param name the database name to open; the database must exist
   * @param user the user name for the database connection (null if not applicable)
   * @param pw the password for the database connection (null if not applicable)
   */
  GenericDatabase::GenericDatabase (DB_ENGINE t, QString srv, int port, QString name, QString user, QString pw)
  {
    initDB(t, srv, port, name, user, pw);
  }
  
//----------------------------------------------------------------------------
    
  GenericDatabase::GenericDatabase(QString sqliteFileName, bool createNew = true)
  {
    initDB(SQLITE, sqliteFileName, createNew ? FAKED_PORT_NUM_FOR_CREATING_NEW_SQLITE_FILE : FAKED_PORT_NUM_FOR_OPENING_EXISTING_SQLITE_FILE, "", "", "");
  }  

//----------------------------------------------------------------------------
    
  GenericDatabase::GenericDatabase()
  {
    initDB(SQLITE, ":memory:", FAKED_PORT_NUM_FOR_CREATING_NEW_SQLITE_FILE, "", "", "");
  }

//----------------------------------------------------------------------------
  
  /**
   * Does the real initialization work. Is called from various constructors with different
   * parameter combinations.
   * 
   * @param t the database engine type
   * @param srv the name of the database server or null for DBMS-specific default; for SQLITE, this is the path to the SQLite files
   * @param port the port of the database server to connect to or 0 for DBMS-specific default; special values for SQLite to indicate creating of a new file vs. opening of an existing
   * @param name the database name to open; the database must exist
   * @param user the user name for the database connection (null if not applicable)
   * @param pw the password for the database connection (null if not applicable)
   */
  void GenericDatabase::initDB (DB_ENGINE t, QString srv, int port, QString name, QString user, QString pw)
  {
    dbType = t;
    dbName = name;
    dbServer = srv;
    dbUser = user;
    dbPasswd = pw;
    dbPort = port;

    // generate an internal name for this connection
    internalConnectionName = QString::number(connectionCounter);
    connectionCounter++;

    // initialize the logger
    log = Logger ("DB Overlay (connection " + internalConnectionName + ")");
    
    if (t == SQLITE)
    {
      dbName = QString::null;
      dbUser = QString::null;
      dbPasswd = QString::null;

      // check if the database file exists
      QFile f(srv);
      if ((!f.exists()) && (port == FAKED_PORT_NUM_FOR_OPENING_EXISTING_SQLITE_FILE))
      {
        QString msg = "Database file " + srv + " does not exist and a new file shall not be created";
        log.critical(msg);
        throw runtime_error(QString2String(msg));
      }

      // Acquire a lock on the database mutex before creating the new DB
      //
      // The mutex will be automatically unlocked when we leave this scope
      {
          lock_guard<mutex> mutexGuard{dbMutex};

          QSqlDatabase conn = QSqlDatabase::addDatabase("QSQLITE", internalConnectionName);
          assert(conn.isValid());
          conn.setDatabaseName(srv);
          if (!conn.open())
          {
              QString msg = "Database file " + srv + " could not be opened or created!";
              log.critical(msg);
              throw runtime_error(QString2String(msg));
          }
      }
      
      log.info("Successfully opened / created database file " + srv);

      // reset the dbPort num
      dbPort = -1;

      // in case of SQLite databases, explicitly enable support for foreign keys
      // and disable synchronous writes for better performance
      execNonQuery("PRAGMA foreign_keys = ON");
      enforceSynchronousWrites(false);
    }
    
    else if (t == MYSQL)
    {
      // apply some defaults
      if ((dbServer == QString::null) || (dbServer.length() == 0))
      {
        dbServer = "localhost";
      }
      if (dbPort == 0)
      {
        dbPort = MYSQL_DEFAULT_PORT;
      }

      // Acquire a lock on the database mutex before creating the new DB
      //
      // The mutex will be automatically unlocked when we leave this scope
      {
          lock_guard<mutex> mutexGuard{dbMutex};
          QSqlDatabase conn = QSqlDatabase::addDatabase("QMYSQL", internalConnectionName);
          assert(conn.isValid());
          conn.setHostName(srv);
          conn.setDatabaseName(dbName);
          conn.setUserName(dbUser);
          conn.setPassword(dbPasswd);
          conn.setPort(dbPort);
          if (!conn.open())
          {
              QString msg = "Could not open database " + dbName + " on server " + srv;
              log.critical(msg);
              throw runtime_error(QString2String(msg));
          }
      }
      
      log.info("Successfully opened database " + dbName + " on server " + srv);
    }
    else
    {
      QString msg = "Unknown database type!";
      log.critical(msg);
      throw runtime_error(QString2String(msg));
    }

    // clear the tab cache, because other database instances may have
    // been opened before
    DbTab::clearTabCache();
    
    // prepare a cache for foreign key clauses during table creation
    foreignKeyCreationCache.clear();

  }

//----------------------------------------------------------------------------
    
  GenericDatabase::~GenericDatabase()
  {
    // Do not call close() from destructor, or else copy-constructors don't
    // work anymore.
    //
    // So we have to call close() explicitly on application level)
    //close();
  }
    
//----------------------------------------------------------------------------
    
  void GenericDatabase::close()
  {
    lock_guard<mutex> mutexGuard{dbMutex};

    // call the following two statements in a separate scope to make sure
    // that "conn" goes out of scope before we remove the DB
    // Otherwise we get warnings about pending queries when calling removeDatabase
    {
      QSqlDatabase conn = QSqlDatabase::database(internalConnectionName);
      if (conn.isValid() && conn.isOpen())
      {
          conn.close();
      }
    }
    QSqlDatabase::removeDatabase(internalConnectionName);
    log.info("Database connection to " + dbServer + " closed.");
  }
    
//----------------------------------------------------------------------------
  
  int GenericDatabase::execNonQuery(const QString& baseSqlStatement)
  {
    return execNonQuery(baseSqlStatement, QVariantList());
  }
    
//----------------------------------------------------------------------------
  
  int GenericDatabase::execNonQuery(const QString& baseSqlStatement, const QVariantList& params)
  {
    unique_ptr<QSqlQuery> qry = execContentQuery(baseSqlStatement, params);
    
    if (qry == NULL)
    {
      return -1;
    }
    
    int result;
    if (qry->isSelect())
    {
      result = qry->size();
    }
    else
    {
      result = qry->numRowsAffected();
    }
    
    return result;
  }
    
//----------------------------------------------------------------------------

  QVariant GenericDatabase::execScalarQuery(const QString& baseSqlStatement, const QVariantList& params)
  {
    unique_ptr<QSqlQuery> qry = execContentQuery(baseSqlStatement, params);
    
    if (qry == nullptr)
    {
      return QVariant(); // invalid QVariant indicates error
    }
    
    if (!(qry->first()))
    {
      log.warn("Scalar Query returned no data!" + QString("\n") + "     " + qry->lastQuery() + QString("\n"));
      return QVariant(); // invalid QVariant indicates error
    }
    
    QVariant result = qry->value(0);
    return result;
  }
    
//----------------------------------------------------------------------------

  unique_ptr<QSqlQuery> GenericDatabase::execContentQuery(const QString& baseSqlStatement, const QVariantList& params)
  {
    // all queries finally end up here. Make sure we are the only ones
    // to access the database at a time
    //
    // The mutex will be automatically unlocked when we leave this function
    lock_guard<mutex> mutexGuard{dbMutex};

    unique_ptr<QSqlQuery> qry { prepStatement(baseSqlStatement, params)};
    
    bool ok = qry->exec();
    queryCounter++;
    
    if (!ok)
    {
      dumpError(qry);
      return nullptr;
    }
    
    int result;
    if (qry->isSelect())
    {
      result = qry->size();
    }
    else
    {
      result = qry->numRowsAffected();
    }
    
    dumpSuccessInfo(qry, result);
    
    return qry;
  }
    
//----------------------------------------------------------------------------

  void GenericDatabase::dumpError(unique_ptr<QSqlQuery> const &qry, bool throwException)
  {
    QString msg = "The following SQL query failed: " + QString("\n");
    msg += "     " + qry->lastQuery() + QString("\n");
    msg += "     Error: " + qry->lastError().text()  + QString("\n");
    log.warn(msg);
    
    if (throwException)
    {
      throw runtime_error(QString2String(msg));
    }
  }
    
//----------------------------------------------------------------------------

  void GenericDatabase::dumpSuccessInfo(unique_ptr<QSqlQuery> const &qry, int result)
  {
    QString msg = "The following SQL query was successfully executed: " + QString("\n");
    msg += "     " + qry->lastQuery() + QString("\n");
    msg += "     Rows affected: " + QString::number(result)  + QString("\n");
    log.info(msg);  
  }
    
//----------------------------------------------------------------------------

  unique_ptr<QSqlQuery> GenericDatabase::prepStatement(const QString& baseSqlStatement, const QVariantList& params)
  {
    QSqlDatabase conn = QSqlDatabase::database(internalConnectionName);
    if (!(conn.isValid() && conn.isOpen()))
    {
        throw runtime_error("Attempt to access closed database!");
    }

    unique_ptr<QSqlQuery> qry {new QSqlQuery(conn) };
    assert(qry != nullptr);
    
    qry->prepare(baseSqlStatement);
    
    for (int i=0; i < params.size(); i++)
    {
      qry->addBindValue(params.at(i));
    }
    
    return qry;
  }
    
//----------------------------------------------------------------------------

  /**
   * Enables or disables synchronous writes for SQLite databases. Has no effect for other database systems.
   * 
   * @param syncOn set to true to enable synchronous writes or to false to disable them
   */
  void GenericDatabase::enforceSynchronousWrites(bool syncOn)
  {
    if (dbType != SQLITE)
    {
      return;
    }
    
    QString sql = "PRAGMA synchronous = O";
    if (syncOn)
    {
      sql += "N";
    }
    else
    {
      sql += "FF";
    }
    
    execNonQuery(sql);
  }
    
//----------------------------------------------------------------------------

  /**
   * Helper function for easy table creation, e. g. from within populateTables
   * 
   * @param tabName contains the name of the table to be created
   * @param colDefs is a list of column definitions for this table
   */
  void GenericDatabase::tableCreationHelper(const QString& tabName, const QList<QString>& colDefs)
  {
    QString sql = "CREATE TABLE IF NOT EXISTS " + tabName + " (";
    sql += "id INTEGER NOT NULL PRIMARY KEY ";
    
    if (dbType == MYSQL) sql += "AUTO_INCREMENT";
    else  sql += "AUTOINCREMENT";
    
    sql += ", " + commaSepStringFromList(colDefs);
    
    if (foreignKeyCreationCache.length() != 0) {
      sql += ", " + commaSepStringFromList(foreignKeyCreationCache);
      foreignKeyCreationCache.clear();
    }

    sql += ");";
    execNonQuery(sql);
  }
  
//----------------------------------------------------------------------------

  /**
   * Helper function for easy view creation, e. g. from within populateViews
   * 
   * @param viewName contains the name of the view to be created
   * @param selectStmt is the sql-select-statement for this view
   */    
  void GenericDatabase::viewCreationHelper(const QString& viewName, const QString& selectStmt)
  {
    QString sql = "CREATE VIEW IF NOT EXISTS";
    if (dbType == MYSQL) sql = "CREATE OR REPLACE VIEW";

    sql += " " + viewName + " AS ";
    sql += selectStmt;
    execNonQuery(sql);
  }

//----------------------------------------------------------------------------

  /**
   * Return a list of all views or all tables in the database
   * 
   * @param getViews must be set to true to return view names; table names otherwise
   * @return a QStringList of strings with names
   */
  QStringList GenericDatabase::allTableNames(bool getViews)
  {
    QSqlDatabase conn = QSqlDatabase::database(internalConnectionName);
    if (getViews)
    {
      log.info("Found views: " + commaSepStringFromList(conn.tables(QSql::Views)));
      queryCounter++;
      return conn.tables(QSql::Views);
    }
    
    QStringList result = conn.tables(QSql::Tables);
    
    // remove an internal sqlite table
    if ((dbType == SQLITE) && (result.contains("sqlite_sequence")))
    {
      result.removeAll("sqlite_sequence");
    }
    queryCounter++;
    return result;
  }
  
//----------------------------------------------------------------------------

  /**
   * Returns a list of all views in the database
   * 
   * @return the view names as QStringList
   */
  QStringList GenericDatabase::allViewNames()
  {
    return allTableNames(true);
  }
    
//----------------------------------------------------------------------------

  /**
   * Get the current query counter
   * @return the current query counter
   */
  long GenericDatabase::getQueryCounter()
  {
    return queryCounter;
  }
    
//----------------------------------------------------------------------------

  /**
   * Reset the query counter to zero
   */
  void GenericDatabase::resetQueryCounter()
  {
    queryCounter = 0;
  }
    
//----------------------------------------------------------------------------

  /**
   * Checks whether the DB contains a specific view or table
   * 
   * @param name is the name of the view / table to look for
   * @param isView must be set to true if "name" refers to a view
   * @return true if the database contains the table / view named "name"
   */
  bool GenericDatabase::hasTable(const QString& name, bool isView)
  {
    QStringList allNames = allTableNames(isView);
    return allNames.contains(name);
  }
    
//----------------------------------------------------------------------------

  /**
   * Checks whether the DB contains a specific view
   * 
   * @param viewName is the name of the view to look for
   * @return true if the database contains the view named "name"
   */
  bool GenericDatabase::hasView(const QString& name)
  {
    return hasTable(name, true);
  }
    
//----------------------------------------------------------------------------

  /**
   * Helper function to create a FOREIGN-KEY-statement for CREATE TABLE purposes
   * 
   * @param keyName the of the column which will reference to the other table
   * @param referedTable the name of the table to which id-column we will refer to
   * @return the string with the FOREIGN KEY statement
   */
  QString GenericDatabase::genForeignKeyClause(QString keyName, QString referedTable)
  {
    foreignKeyCreationCache << "FOREIGN KEY (" + keyName + ") REFERENCES " + referedTable + "(id)";
    return keyName + " INTEGER";
  }
    
//----------------------------------------------------------------------------

  GenericDatabase::DB_ENGINE GenericDatabase::getDbType()
  {
    return dbType;
  }
    
//----------------------------------------------------------------------------

  int GenericDatabase::getLastInsertId()
  {
    QString sql = "SELECT ";
    
    if (dbType == SQLITE)
    {
      sql += "last_insert_rowid()";
    } else {
      sql += "LAST_INSERT_ID()";
    }
    
    QVariant result = execScalarQuery(sql);
    return result.toInt();
  }

//----------------------------------------------------------------------------

  void GenericDatabase::setLogLevel(int newLvl)
  {
    log.setLevel(newLvl);
  }
    
//----------------------------------------------------------------------------
    
    
//----------------------------------------------------------------------------
    
    
//----------------------------------------------------------------------------
    
    
//----------------------------------------------------------------------------
    
    
//----------------------------------------------------------------------------
    
    
//----------------------------------------------------------------------------
    
    
//----------------------------------------------------------------------------
    
    
//----------------------------------------------------------------------------
    
    
//----------------------------------------------------------------------------
    
    
//----------------------------------------------------------------------------
    
    
//----------------------------------------------------------------------------
    
    
//----------------------------------------------------------------------------
    
    
//----------------------------------------------------------------------------
    
    
//----------------------------------------------------------------------------
    
    
//----------------------------------------------------------------------------
    
    
//----------------------------------------------------------------------------
    
}
