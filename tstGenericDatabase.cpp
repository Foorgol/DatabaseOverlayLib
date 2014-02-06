/* 
 * File:   tstGenericDatabase.cpp
 * Author: volker
 * 
 * Created on February 2, 2014, 1:02 PM
 */

#include "tstGenericDatabase.h"

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



