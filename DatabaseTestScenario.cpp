/* 
 * File:   DatabaseTestScenario.cpp
 * Author: volker
 * 
 * Created on February 2, 2014, 4:30 PM
 */

#include "DatabaseTestScenario.h"

#include <QtSql/QSqlQuery>
#include <QFile>
#include <QtSql/QSqlError>

QSqlDatabase DatabaseTestScenario::getDbConn(dbOverlay::GenericDatabase::DB_ENGINE t, bool inMemory)
{
  if (QSqlDatabase::contains(DB_CONNECTION_NAME))
  {
    QSqlDatabase db = QSqlDatabase::database(DB_CONNECTION_NAME, true);

    // despite providing the database name using setDatabaseName,
    // you must issue a USE SQL-command before actually accessing the database
    if (t == dbOverlay::GenericDatabase::MYSQL)
    {
      QSqlQuery qry(db);
      execQueryAndDumpError(qry, "USE " + MYSQL_DB);
    }
    
    return db;

  }

  QSqlDatabase db;
  
  if (t == dbOverlay::GenericDatabase::SQLITE)
  {
    db = QSqlDatabase::addDatabase("QSQLITE", DB_CONNECTION_NAME);

    QString fName;
    if (inMemory)
    {
      fName = ":memory:";
    } else
    {
      fName = getSqliteFileName();
    }

    db.setDatabaseName(fName);
    
  } else {
    
    db = QSqlDatabase::addDatabase("QMYSQL", DB_CONNECTION_NAME);
    db.setHostName(MYSQL_HOST);
    db.setDatabaseName(MYSQL_DB);
    db.setPort(MYSQL_PORT);
    db.setUserName(DB_USER);
    db.setPassword(DB_PASSWD);
  }
  
  if (!db.open())
  {
    QSqlError err = db.lastError();
    log->warn("db.open() for " + db.hostName() + " using driver " + db.driverName() + " failed with: " + err.text());
    CPPUNIT_ASSERT(false);
  } else {
    log->info("db.open() for " + db.hostName() + " using driver " + db.driverName() + " succeeded!");
  }
  
  // despite providing the database name using setDatabaseName,
  // you must issue a USE SQL-command before actually accessing the database
  if (t == dbOverlay::GenericDatabase::MYSQL)
  {
    QSqlQuery qry(db);
    execQueryAndDumpError(qry, "USE " + MYSQL_DB);
  }
  
  return db;
}

//----------------------------------------------------------------------------
    
QSqlDatabase DatabaseTestScenario::getDbConn()
{
  if (QSqlDatabase::contains(DB_CONNECTION_NAME))
  {
    QSqlDatabase db = QSqlDatabase::database(DB_CONNECTION_NAME, true);

    // despite providing the database name using setDatabaseName,
    // you must issue a USE SQL-command before actually accessing the database
    if (db.driverName() == "QMYSQL")
    {
      QSqlQuery qry(db);
      execQueryAndDumpError(qry, "USE " + MYSQL_DB);
    }
    
    return db;

  }
  
  return getDbConn(dbOverlay::GenericDatabase::SQLITE);

}

//----------------------------------------------------------------------------

void DatabaseTestScenario::cleanupMysql()
{
  QSqlDatabase db = getDbConn(dbOverlay::GenericDatabase::MYSQL);
  
  db.exec("DROP DATABASE " + MYSQL_DB);
  db.exec("CREATE DATABASE " + MYSQL_DB);
}

//----------------------------------------------------------------------------

void DatabaseTestScenario::removeDbConn()
{
  if (QSqlDatabase::contains(DB_CONNECTION_NAME))
  {
    QSqlDatabase::removeDatabase(DB_CONNECTION_NAME);
    CPPUNIT_ASSERT(!QSqlDatabase::contains(DB_CONNECTION_NAME));
    qDebug() << "Removed database " + DB_CONNECTION_NAME + " from connection pool";
  } else {
    qDebug() << "Weird: could not remove database " + DB_CONNECTION_NAME + " from connection pool, because it's not existing";
  }
}

//----------------------------------------------------------------------------

void DatabaseTestScenario::tearDown()
{
  BasicTestClass::tearDown();
  removeDbConn();
  
  qDebug() << "----------- DatabaseTestScenario tearDown() finished! -----------";
}

//----------------------------------------------------------------------------

QString DatabaseTestScenario::getSqliteFileName()
{
  return genTestFilePath(SQLITE_DB);
}

//----------------------------------------------------------------------------
    
bool DatabaseTestScenario::sqliteFileExists()
{
  QFile f(getSqliteFileName());
  return f.exists();
}

//----------------------------------------------------------------------------

void DatabaseTestScenario::prepScenario01(dbOverlay::GenericDatabase::DB_ENGINE t, bool inMemory)
{
  QSqlDatabase db;
  
  if (t == dbOverlay::GenericDatabase::MYSQL)
  {
    cleanupMysql();
    db = getDbConn();
  } else {
    CPPUNIT_ASSERT_ASSERTION_FAIL(sqliteFileExists());
    db = getDbConn(t, inMemory);
    if (!inMemory)
    {
      CPPUNIT_ASSERT(sqliteFileExists());
    }
  }

  QString aiStr = (t == dbOverlay::GenericDatabase::MYSQL) ? "AUTO_INCREMENT" : "AUTOINCREMENT";
  QString nowStr = (t == dbOverlay::GenericDatabase::MYSQL) ? "NOW()" : "date('now')";
  QString viewStr = (t == dbOverlay::GenericDatabase::MYSQL) ? "CREATE OR REPLACE VIEW" : "CREATE VIEW IF NOT EXISTS";

  db.exec("CREATE TABLE IF NOT EXISTS t1 (id INTEGER NOT NULL PRIMARY KEY " + aiStr + "," +
          " i INT, f DOUBLE, s VARCHAR(40), d DATETIME)");
  db.exec("CREATE TABLE IF NOT EXISTS t2 (id INTEGER NOT NULL PRIMARY KEY " + aiStr + "," +
          " i INT, f DOUBLE, s VARCHAR(40), d DATETIME)");

  db.exec("INSERT INTO t1 VALUES (NULL, 42, 23.23, 'Hallo', " + nowStr + ")");
  db.exec("INSERT INTO t1 VALUES (NULL, NULL, 666.66, 'Hi', " + nowStr + ")");
  db.exec("INSERT INTO t1 VALUES (NULL, 84, NULL, 'Ho', " + nowStr + ")");
  db.exec("INSERT INTO t1 VALUES (NULL, 84, NULL, 'Hoi', " + nowStr + ")");
  db.exec("INSERT INTO t1 VALUES (NULL, 84, 42.42, 'Ho', " + nowStr + ")");

  db.exec(viewStr + " v1 AS SELECT i, f, s FROM t1 WHERE i=84");

}

//----------------------------------------------------------------------------

void DatabaseTestScenario::execQueryAndDumpError(QSqlQuery& qry, const QString& sqlStatement)
{
  bool ok;
  if (sqlStatement.length() != 0)
  {
    // simple statement
    ok = qry.exec(sqlStatement);
  } else {
    // prepared statement, prepared externally
    ok = qry.exec();
  }
  
  if (!ok)
  {
    QString msg = "The following SQL query failed: " + QString("\n");
    msg += "     " + qry.lastQuery() + QString("\n");
    msg += "     Error: " + qry.lastError().text()  + QString("\n");
    log->warn(msg);
    CPPUNIT_ASSERT(false);
  } else {
    
    int result;
    if (qry.isSelect())
    {
      result = qry.size();
    }
    else
    {
      result = qry.numRowsAffected();
    }
    
    QString msg = "The following SQL query was successfully executed: " + QString("\n");
    msg += "     " + qry.lastQuery() + QString("\n");
    msg += "     Rows affected: " + QString::number(result)  + QString("\n");
    log->info(msg);  

  }
}

//----------------------------------------------------------------------------
    

//----------------------------------------------------------------------------
    

//----------------------------------------------------------------------------
    
