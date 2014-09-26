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

#include "tstGenericDatabase.h"
#include "dbExceptions.h"
#include "DbTab.h"

#include <stdexcept>

#include <QList>
#include <qt/QtCore/qstringlist.h>
#include <qt/QtCore/qmetatype.h>

using namespace dbOverlay;

void tstGenericDatabase::testConstructorMySql()
{
  printStartMsg("testConstructorMySql");
  
  // open existing database using explicit parameters
  SampleDB db1(dbOverlay::GenericDatabase::MYSQL, "localhost", 3306, "unittest", "unittest", "unittest");
  
  // open existing database using default parameters
  SampleDB db2(dbOverlay::GenericDatabase::MYSQL, QString::null, 0,  "unittest", "unittest", "unittest");
  SampleDB db3(dbOverlay::GenericDatabase::MYSQL, "", 0,  "unittest", "unittest", "unittest");
  
  // open non-existing DB
  CPPUNIT_ASSERT_THROW(SampleDB db3(dbOverlay::GenericDatabase::MYSQL, "sdfjhsdf", 3306, "unittest", "unittest", "unittest"), std::runtime_error);

  printEndMsg();
  
}

//----------------------------------------------------------------------------

void tstGenericDatabase::testPopulate()
{
  printStartMsg("testPopulate");
  
  cleanupMysql();
  SampleDB db(dbOverlay::GenericDatabase::MYSQL, "localhost", 3306, "unittest", "unittest", "unittest");
  db.populateTables();
  db.populateViews();
  
  // make sure all tables have been created
  QSqlDatabase dbDirect = getDbConn();
  QSqlQuery qry(dbDirect);
  execQueryAndDumpError(qry, "SHOW TABLES");
  CPPUNIT_ASSERT(qry.first());
  CPPUNIT_ASSERT(qry.value(0).toString() == "t1");
  CPPUNIT_ASSERT(qry.next());
  CPPUNIT_ASSERT(qry.value(0).toString() == "t2");
  CPPUNIT_ASSERT(qry.next());
  CPPUNIT_ASSERT(qry.value(0).toString() == "v1");
  CPPUNIT_ASSERT(!qry.next());

  //
  // Execute the same tests for a SQLite database
  //
  removeDbConn();
  
  SampleDB db1(getSqliteFileName(), true);
  db1.populateTables();
  db1.populateViews();

  // make sure all tables have been created
  dbDirect = getDbConn(dbOverlay::GenericDatabase::SQLITE);
  qry = QSqlQuery(dbDirect);
  CPPUNIT_ASSERT(dbDirect.driverName() == "QSQLITE");
  execQueryAndDumpError(qry, "SELECT * FROM sqlite_master WHERE type='table'");
  CPPUNIT_ASSERT(qry.first());
  CPPUNIT_ASSERT(qry.value(1).toString() == "t1");
  CPPUNIT_ASSERT(qry.next());
  CPPUNIT_ASSERT(qry.next());  // skip one sqlite-internal entry
  CPPUNIT_ASSERT(qry.value(1).toString() == "t2");
  CPPUNIT_ASSERT(!qry.next());
  
  execQueryAndDumpError(qry, "SELECT * FROM sqlite_master WHERE type='view'");
  CPPUNIT_ASSERT(qry.first());
  CPPUNIT_ASSERT(qry.value(1).toString() == "v1");
  CPPUNIT_ASSERT(!qry.next());
  
  printEndMsg();
}

//----------------------------------------------------------------------------

void tstGenericDatabase::testConstructorSQLite()
{
  printStartMsg("testConstructorSQLite");

  // Make sure the db file does not exists
  CPPUNIT_ASSERT(!sqliteFileExists());
  
  // create an in-memory database
  SampleDB db3;
  CPPUNIT_ASSERT(!sqliteFileExists());
  
  // create a new, empty file
  SampleDB db(getSqliteFileName(), true);
  CPPUNIT_ASSERT(sqliteFileExists());
  
  // close the connection
  db.close();
  
  // open an existing file
  SampleDB db1(getSqliteFileName(), false);
  db1.close();
  
  // try to open a non-existing file
  CPPUNIT_ASSERT_THROW(SampleDB db2("dfkjsdfhksd", false), std::runtime_error);

  printEndMsg();
  
}

//----------------------------------------------------------------------------

void tstGenericDatabase::testGetTableNames()
{
  printStartMsg("testGetTableNames");
  
  QList<dbOverlay::GenericDatabase::DB_ENGINE> dbTypes;
  dbTypes.append(dbOverlay::GenericDatabase::SQLITE);
  dbTypes.append(dbOverlay::GenericDatabase::MYSQL);
  
  QList<dbOverlay::GenericDatabase::DB_ENGINE>::iterator i;
  for (i = dbTypes.begin(); i != dbTypes.end(); ++i)
  {
    SampleDB db = getScenario01(*i);
    
    QStringList allTabs = db.allTableNames();
    CPPUNIT_ASSERT_EQUAL(2, allTabs.length());
    CPPUNIT_ASSERT(allTabs.contains("t1"));
    CPPUNIT_ASSERT(allTabs.contains("t2"));
    
    QStringList allViews = db.allViewNames();
    CPPUNIT_ASSERT_EQUAL(1, allViews.length());
    CPPUNIT_ASSERT(allViews.contains("v1"));
    
    // remove the connection of the "Object under test"
    db.close();
    
    // remove the connection of the unittest framework
    removeDbConn();
  }
  
  printEndMsg();
}

//----------------------------------------------------------------------------

void tstGenericDatabase::testHasTable()
{
  printStartMsg("testHasTable");

  QList<dbOverlay::GenericDatabase::DB_ENGINE> dbTypes;
  dbTypes.append(dbOverlay::GenericDatabase::SQLITE);
  dbTypes.append(dbOverlay::GenericDatabase::MYSQL);
  
  QList<dbOverlay::GenericDatabase::DB_ENGINE>::iterator i;
  for (i = dbTypes.begin(); i != dbTypes.end(); ++i)
  {
    SampleDB db = getScenario01(*i);
    
    CPPUNIT_ASSERT(db.hasTable("t1"));
    CPPUNIT_ASSERT(!db.hasTable("sadasda"));
    CPPUNIT_ASSERT(!db.hasTable(""));
    CPPUNIT_ASSERT(!db.hasTable(QString::null));
    
    CPPUNIT_ASSERT(db.hasView("v1"));
    CPPUNIT_ASSERT(!db.hasView("sadasda"));
    CPPUNIT_ASSERT(!db.hasView(""));
    CPPUNIT_ASSERT(!db.hasView(QString::null));
    
    // remove the connection of the "Object under test"
    db.close();
    
    // remove the connection of the unittest framework
    removeDbConn();
  }  
  
  printEndMsg();
}

//----------------------------------------------------------------------------

void tstGenericDatabase::testExecScalarQuery()
{
  printStartMsg("testExecScalarQuery");
  
  SampleDB db = getScenario01(dbOverlay::GenericDatabase::SQLITE);
  
  // test invalid query
  QVariant result = db.execScalarQuery("sdkfhsdkf");
  CPPUNIT_ASSERT(!result.isValid());
  
  // test query that returns no data
  // use the chance to test sql statement construction as well
  QVariantList params;
  params << 456;
  result = db.execScalarQuery("SELECT id FROM t1 WHERE i>?", params);
  CPPUNIT_ASSERT(!result.isValid());
  
  // test valid query with result
  params.clear();
  params << 84;
  result = db.execScalarQuery("SELECT count(id) FROM t1 WHERE i=?", params);
  CPPUNIT_ASSERT(result.isValid());
  CPPUNIT_ASSERT(result.toInt() == 3);
  
  // test valid query with result that contains more than one row
  result = db.execScalarQuery("SELECT * FROM t1 WHERE f IS NULL");
  CPPUNIT_ASSERT(result.isValid());
  CPPUNIT_ASSERT(result.toInt() == 3);  // the row ID of the first result row
  
  printEndMsg();
}

//----------------------------------------------------------------------------


void tstGenericDatabase::testExecContentQuery()
{
  printStartMsg("testExecContentQuery");
  
  SampleDB db = getScenario01(dbOverlay::GenericDatabase::SQLITE);
  
  // test invalid query
  unique_ptr<QSqlQuery> result = db.execContentQuery("sdkfhsdkf");
  CPPUNIT_ASSERT(result == NULL);
  
  // test query that returns no data
  // use the chance to test sql statement construction as well
  QVariantList params;
  params << 456;
  result = db.execContentQuery("SELECT id FROM t1 WHERE i>?", params);
  CPPUNIT_ASSERT(result != NULL);
  CPPUNIT_ASSERT(!result->first());
  
  // test valid query with result
  params.clear();
  params << 84;
  result = db.execContentQuery("SELECT count(id) FROM t1 WHERE i=?", params);
  CPPUNIT_ASSERT(result != NULL);
  CPPUNIT_ASSERT(result->first());
  CPPUNIT_ASSERT(result->value(0).toInt() == 3);
  CPPUNIT_ASSERT(!result->next());
  
  // test valid query with result that contains more than one row
  result = db.execContentQuery("SELECT * FROM t1 WHERE f IS NULL");
  CPPUNIT_ASSERT(result != NULL);
  CPPUNIT_ASSERT(result->first());
  CPPUNIT_ASSERT(result->value(0).toInt() == 3);
  CPPUNIT_ASSERT(result->value(1).toInt() == 84);
  CPPUNIT_ASSERT(result->value(3).toString() == "Ho");
  CPPUNIT_ASSERT(result->next());
  CPPUNIT_ASSERT(result->value(0).toInt() == 4);
  CPPUNIT_ASSERT(result->value(1).toInt() == 84);
  CPPUNIT_ASSERT(result->value(3).toString() == "Hoi");
  CPPUNIT_ASSERT(!result->next());
  
  printEndMsg();
}

//----------------------------------------------------------------------------

void tstGenericDatabase::testGetTab()
{
  printStartMsg("testGetTab");
  
  SampleDB db = getScenario01(dbOverlay::GenericDatabase::SQLITE);
  
  // test invalid query
  CPPUNIT_ASSERT_THROW(db.getTab(""), InvalidTabNameException);
  CPPUNIT_ASSERT_THROW(db.getTab(QString::null), InvalidTabNameException);
  CPPUNIT_ASSERT_THROW(db.getTab("Lalala"), InvalidTabNameException);
  
  // test valid query
  DbTab t1 = db.getTab("t1");
  
  // make sure that another request to this table
  // does not result in another db query
  db.resetQueryCounter();
  DbTab t1_2 = db.getTab("t1");
  CPPUNIT_ASSERT(db.getQueryCounter() == 0);
  
  // make sure that a request to another table
  // actually result in another db query
  db.resetQueryCounter();
  DbTab t2 = db.getTab("t2");
  CPPUNIT_ASSERT(db.getQueryCounter() > 0);
  
  //
  // Repeat all tests above using the []-operator
  //
  
  DbTab::clearTabCache();
  
  // test invalid query
  CPPUNIT_ASSERT_THROW(db[""], InvalidTabNameException);
  CPPUNIT_ASSERT_THROW(db[QString::null], InvalidTabNameException);
  CPPUNIT_ASSERT_THROW(db["Lalala"], InvalidTabNameException);
  
  // test valid query
  t1 = db["t1"];
  
  // make sure that another request to this table
  // does not result in another db query
  db.resetQueryCounter();
  t1_2 = db["t1"];
  CPPUNIT_ASSERT(db.getQueryCounter() == 0);
  
  // make sure that a request to another table
  // actually result in another db query
  db.resetQueryCounter();
  t2 = db["t2"];
  CPPUNIT_ASSERT(db.getQueryCounter() > 0);
  
  printEndMsg();
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


//----------------------------------------------------------------------------


//----------------------------------------------------------------------------


//----------------------------------------------------------------------------



