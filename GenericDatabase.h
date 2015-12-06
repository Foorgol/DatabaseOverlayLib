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

#ifndef GENERICDATABASE_H
#define	GENERICDATABASE_H

#include <string>
#include <mutex>
#include <QtCore>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QList>
#include <QStringList>
#include <QVariant>
#include <memory>

#include "Logger.h"

using namespace std;

namespace dbOverlay
{
  // forward def for DbTab as return type (see below)
  class DbTab;

  class GenericDatabase
  {

  public:
    /**
     * An enum to identify the database type for the connection
     */
    enum DB_ENGINE
    {
      SQLITE,
      MYSQL
    };


    GenericDatabase ();
    GenericDatabase(QString sqliteFileName, bool createNew);
    GenericDatabase(DB_ENGINE t, QString srv, int port, QString name, QString user, QString pw);
    
    virtual ~GenericDatabase ();
    
    int execNonQuery(const QString& baseSqlStatement, const QVariantList& params);
    int execNonQuery(const QString& baseSqlStatement);
    QVariant execScalarQuery(const QString& baseSqlStatement, const QVariantList& params = QVariantList());
    unique_ptr<QSqlQuery> execContentQuery(const QString& baseSqlStatement, const QVariantList& params = QVariantList());
    void enforceSynchronousWrites(bool syncOn);
    
    virtual void populateTables() = 0;
    virtual void populateViews() = 0;
    
    void tableCreationHelper(const QString& tabName, const QList<QString>& colDefs);
    void viewCreationHelper(const QString& viewName, const QString& selectStmt);
    void indexCreationHelper(const QString& tabName, const QString& idxName, const QList<QString>& colNames, bool isUnique=false);
    void indexCreationHelper(const QString& tabName, const QString& idxName, const QString& colName, bool isUnique=false);
    void indexCreationHelper(const QString& tabName, const QString& colName, bool isUnique=false);

    void close();
    
    QStringList allTableNames(bool getViews=false);
    QStringList allViewNames();
    
    long getQueryCounter();
    void resetQueryCounter();
    bool hasTable(const QString& name, bool isView=false);
    bool hasView(const QString& name);
    QString genForeignKeyClause(QString keyName, QString referedTable);
    DB_ENGINE getDbType();
    DbTab getTab(const QString& name);
    DbTab operator[](const QString& name);
    int getLastInsertId();

    void setLogLevel(int newLvl);
    
    
  private:
    void dumpError(unique_ptr<QSqlQuery> const &qry, bool throwException = false);
    void dumpSuccessInfo(unique_ptr<QSqlQuery> const &qry, int result);
    static int connectionCounter;
    QString internalConnectionName;
    static const int MYSQL_DEFAULT_PORT;
    QStringList foreignKeyCreationCache;

  protected:

    /**
     * A logger for error messages
     */
    Logger log;

    /**
     * The connection object for the database handled by this class
     */
    mutable mutex dbMutex;

    /**
     * The user name for the database server
     */
    QString dbUser;

    /**
     * The password for the database server
     */
    QString dbPasswd;

    /**
     * The name of the database to be accessed
     */
    QString dbName;

    /**
     * The database type for the connection
     */
    DB_ENGINE dbType;

    /**
     * The name of the server to connect to
     */
    QString dbServer;

    /**
     * The server port to connect to
     */
    int dbPort;

    /**
     * A counter for executed queries; for debugging purposes only
     */
    long queryCounter;

    static const int FAKED_PORT_NUM_FOR_CREATING_NEW_SQLITE_FILE = -100;
    static const int FAKED_PORT_NUM_FOR_OPENING_EXISTING_SQLITE_FILE = -200;
    
    void initDB(DB_ENGINE t, QString srv, int port, QString name, QString user, QString pw);
    
    unique_ptr<QSqlQuery> prepStatement(const QString& baseSqlStatement, const QVariantList& params);
    
  };
}
#endif	/* GENERICDATABASE_H */

