/* 
 * File:   DatabaseTestScenario.h
 * Author: volker
 *
 * Created on February 2, 2014, 4:30 PM
 */

#ifndef DATABASETESTSCENARIO_H
#define	DATABASETESTSCENARIO_H

#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include <QtSql/QSqlDatabase>

#include "BasicTestClass.h"
#include "GenericDatabase.h"
#include "SampleDB.h"

class DatabaseTestScenario : public BasicTestClass
{
public:

protected:
  const QString DB_CONNECTION_NAME = "unittest";
  const QString DB_USER = "unittest";
  const QString DB_PASSWD = "unittest";
  const QString MYSQL_HOST = "localhost";
  const QString MYSQL_DB = "unittest";
  const int MYSQL_PORT = 3306;

  const QString SQLITE_DB = "SqliteTestDB.db";

  QSqlDatabase getDbConn(dbOverlay::GenericDatabase::DB_ENGINE t);
  QSqlDatabase getDbConn();
  void removeDbConn();
  void cleanupMysql();
  
  void prepScenario01(dbOverlay::GenericDatabase::DB_ENGINE t);
  SampleDB getScenario01(dbOverlay::GenericDatabase::DB_ENGINE t);
  
  void execQueryAndDumpError(QSqlQuery& qry, const QString& sqlStatement="");

public:
  virtual void tearDown ();
  QString getSqliteFileName();
  bool sqliteFileExists();
};

#endif	/* DATABASETESTSCENARIO_H */

