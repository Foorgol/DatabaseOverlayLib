/* 
 * File:   tstGenericDatabase.cpp
 * Author: volker
 * 
 * Created on February 2, 2014, 1:02 PM
 */

#include "tstGenericDatabase.h"

#include <stdexcept>

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
  dbDirect = getDbConn(dbOverlay::GenericDatabase::SQLITE, false);
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


//----------------------------------------------------------------------------


//----------------------------------------------------------------------------


//----------------------------------------------------------------------------


//----------------------------------------------------------------------------



