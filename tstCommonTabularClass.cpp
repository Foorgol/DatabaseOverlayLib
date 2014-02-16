/* 
 * File:   tstGenericDatabase.cpp
 * Author: volker
 * 
 * Created on February 2, 2014, 1:02 PM
 */

#include "tstCommonTabularClass.h"
#include "dbExceptions.h"
#include "../qt4/QtCore/qchar.h"
#include "HelperFunc.h"

#include <stdexcept>

#include <QList>
#include <qt/QtCore/qstringlist.h>
#include <qt/QtCore/qmetatype.h>
#include <qt/QtCore/qjsonarray.h>

using namespace dbOverlay;

void tstCommonTabularClass::testConstructor()
{
  printStartMsg("testConstructor");
  
  SampleDB db = getScenario01(dbOverlay::GenericDatabase::SQLITE);
  
  // test NULL ptr to db
  CPPUNIT_ASSERT_THROW(CommonTabularClass t(NULL, "Lala", true), EmptyDatabaseHandleException);
  
  // test invalid table / view name
  CPPUNIT_ASSERT_THROW(CommonTabularClass t(&db, "", true), InvalidTabNameException);
  CPPUNIT_ASSERT_THROW(CommonTabularClass t(&db, "", false), InvalidTabNameException);
  CPPUNIT_ASSERT_THROW(CommonTabularClass t(&db, "Lala", true), InvalidTabNameException);
  CPPUNIT_ASSERT_THROW(CommonTabularClass t(&db, "Lala", false), InvalidTabNameException);
  CPPUNIT_ASSERT_THROW(CommonTabularClass t(&db, "t1", true), InvalidTabNameException);
  CPPUNIT_ASSERT_THROW(CommonTabularClass t(&db, "v1", false), InvalidTabNameException);
  
  // test valid calls
  CommonTabularClass t(&db, "t1");
  CommonTabularClass v(&db, "v1", true);

  printEndMsg();
  
}

//----------------------------------------------------------------------------

void tstCommonTabularClass::testAllColDefs()
{
  printStartMsg("testAllColDefs");
  
  QList<dbOverlay::GenericDatabase::DB_ENGINE> dbTypes;
  dbTypes.append(dbOverlay::GenericDatabase::SQLITE);
  dbTypes.append(dbOverlay::GenericDatabase::MYSQL);
  
  QList<dbOverlay::GenericDatabase::DB_ENGINE>::iterator i;
  for (i = dbTypes.begin(); i != dbTypes.end(); ++i)
  {

    SampleDB db = getScenario01(*i);
    CommonTabularClass ctc(&db, "t1");
    
    dbOverlay::ColInfoList cil = ctc.allColDefs();
    
    CPPUNIT_ASSERT(cil.length() == 5);
    
    ColInfo ci = cil.at(0);
    CPPUNIT_ASSERT(ci.getId() == 0);
    CPPUNIT_ASSERT(ci.getColName() == "id");
    CPPUNIT_ASSERT(ci.getColType().contains("INT"));

    ci = cil.at(1);
    CPPUNIT_ASSERT(ci.getId() == 1);
    CPPUNIT_ASSERT(ci.getColName() == "i");
    CPPUNIT_ASSERT(ci.getColType().contains("INT"));

    ci = cil.at(2);
    CPPUNIT_ASSERT(ci.getId() == 2);
    CPPUNIT_ASSERT(ci.getColName() == "f");
    CPPUNIT_ASSERT(ci.getColType().contains("DOUBLE"));

    ci = cil.at(3);
    CPPUNIT_ASSERT(ci.getId() == 3);
    CPPUNIT_ASSERT(ci.getColName() == "s");
    CPPUNIT_ASSERT(ci.getColType().contains("VARCHAR"));

    ci = cil.at(4);
    CPPUNIT_ASSERT(ci.getId() == 4);
    CPPUNIT_ASSERT(ci.getColName() == "d");
    CPPUNIT_ASSERT(ci.getColType().contains("DATE"));

    // remove the connection of the "Object under test"
    db.close();
    
    // remove the connection of the unittest framework
    removeDbConn();
  }

  printEndMsg();
  
}

//----------------------------------------------------------------------------

void tstCommonTabularClass::testGetColType()
{
  printStartMsg("testGetColType");
  
  SampleDB db = getScenario01(dbOverlay::GenericDatabase::SQLITE);
  CommonTabularClass t1(&db, "t1");
  
  // test invalid column names
  CPPUNIT_ASSERT(t1.getColType("Lalala") == QString::null);
  CPPUNIT_ASSERT(t1.getColType("") == QString::null);
  CPPUNIT_ASSERT(t1.getColType(QString::null) == QString::null);
  
  // test normal column
  CPPUNIT_ASSERT(t1.getColType("f") == "DOUBLE");

  printEndMsg();
  
}

//----------------------------------------------------------------------------

void tstCommonTabularClass::testcid2name()
{
  printStartMsg("testcid2name");
  
  SampleDB db = getScenario01(dbOverlay::GenericDatabase::SQLITE);
  CommonTabularClass t1(&db, "t1");
  
  // test invalid column indices
  CPPUNIT_ASSERT(t1.cid2name(-1) == QString::null);
  CPPUNIT_ASSERT(t1.cid2name(200) == QString::null);
  
  // test normal column
  CPPUNIT_ASSERT(t1.cid2name(0) == "id");
  CPPUNIT_ASSERT(t1.cid2name(1) == "i");

  printEndMsg();
  
}

//----------------------------------------------------------------------------

void tstCommonTabularClass::testname2cid()
{
  printStartMsg("testname2cid");
  
  SampleDB db = getScenario01(dbOverlay::GenericDatabase::SQLITE);
  CommonTabularClass t1(&db, "t1");
  
  // test invalid column names
  CPPUNIT_ASSERT(t1.name2cid("Lalala") == -1);
  CPPUNIT_ASSERT(t1.name2cid("") == -1);
  CPPUNIT_ASSERT(t1.name2cid(QString::null) == -1);
  
  // test normal column
  CPPUNIT_ASSERT(t1.name2cid("id") == 0);
  CPPUNIT_ASSERT(t1.name2cid("i") == 1);
  CPPUNIT_ASSERT(t1.name2cid("f") == 2);

  printEndMsg();
  
}

//----------------------------------------------------------------------------

void tstCommonTabularClass::testHasColumn()
{
  printStartMsg("testHasColumn");
  
  SampleDB db = getScenario01(dbOverlay::GenericDatabase::SQLITE);
  CommonTabularClass t1(&db, "t1");
  
  // test invalid column names
  CPPUNIT_ASSERT(t1.hasColumn("Lalala") == false);
  CPPUNIT_ASSERT(t1.hasColumn("") == false);
  CPPUNIT_ASSERT(t1.hasColumn(QString::null) == false);
  
  // test normal column
  CPPUNIT_ASSERT(t1.hasColumn("id"));
  CPPUNIT_ASSERT(t1.hasColumn("i"));
  CPPUNIT_ASSERT(t1.hasColumn("f"));

  // test invalid column indices
  CPPUNIT_ASSERT(t1.hasColumn(-1) == false);
  CPPUNIT_ASSERT(t1.hasColumn(200) == false);
  
  // test normal column
  CPPUNIT_ASSERT(t1.hasColumn(0));
  CPPUNIT_ASSERT(t1.hasColumn(1));
  CPPUNIT_ASSERT(t1.hasColumn(4));

  printEndMsg();
  
}
//----------------------------------------------------------------------------

void tstCommonTabularClass::testGetMatchCountForWhereClause()
{
  printStartMsg("testGetMatchCountForWhereClause");
  
  SampleDB db = getScenario01(dbOverlay::GenericDatabase::SQLITE);
  CommonTabularClass t1(&db, "t1");
  
  // test invalid or empty where clause
  QVariantList qvl;
  CPPUNIT_ASSERT(t1.getMatchCountForWhereClause("") == -1);
  CPPUNIT_ASSERT(t1.getMatchCountForWhereClause(QString::null) == -1);
  CPPUNIT_ASSERT(t1.getMatchCountForWhereClause("lkdflsjflsdf") == -1);
  
  // test valid queries without parameters
  CPPUNIT_ASSERT(t1.getMatchCountForWhereClause("i = 84") == 3);
  
  // test valid query with parameters
  qvl << "Ho";
  qvl << 50;
  CPPUNIT_ASSERT(t1.getMatchCountForWhereClause("s = ? AND i > ?", qvl) == 2);
  
  // test a query that matches zero rows
  qvl.clear();
  qvl << 5000;
  CPPUNIT_ASSERT(t1.getMatchCountForWhereClause("i > ?", qvl) == 0);
  
  // test a wrong number of parameters
  qvl.clear();
  CPPUNIT_ASSERT(t1.getMatchCountForWhereClause("s = ? AND i > ?", qvl) == -1);
  
  printEndMsg();
}

//----------------------------------------------------------------------------

void tstCommonTabularClass::testGetMatchCountForColumnValue()
{
  printStartMsg("testGetMatchCountForColumnValue");
  
  SampleDB db = getScenario01(dbOverlay::GenericDatabase::SQLITE);
  CommonTabularClass t1(&db, "t1");
  
  // test invalid or empty arguments list
  QVariantList qvl;
  CPPUNIT_ASSERT(t1.getMatchCountForColumnValue(qvl) == -1);
  
  qvl << "Odd number of parameters makes no sense";
  CPPUNIT_ASSERT(t1.getMatchCountForColumnValue(qvl) == -1);
  
  qvl.clear();
  qvl << "InvalidColName";
  qvl << "42";
  CPPUNIT_ASSERT(t1.getMatchCountForColumnValue(qvl) == -1);
  
  // test valid query with parameters
  qvl.clear();
  qvl << "i";
  qvl << 84;
  CPPUNIT_ASSERT(t1.getMatchCountForColumnValue(qvl) == 3);
  
  // two parameters, ANDed, incl. NULL
  qvl.clear();
  qvl << "i";
  qvl << 84;
  qvl << "f";
  qvl << QVariant::Int;
  CPPUNIT_ASSERT(t1.getMatchCountForColumnValue(qvl) == 2);
  
  // test a query that matches zero rows
  qvl.clear();
  qvl << "i";
  qvl << 5000;
  CPPUNIT_ASSERT(t1.getMatchCountForColumnValue(qvl) == 0);
  
  printEndMsg();
}

//----------------------------------------------------------------------------

void tstCommonTabularClass::testGetLength()
{
  printStartMsg("testGetLength");
  
  SampleDB db = getScenario01(dbOverlay::GenericDatabase::SQLITE);
  CommonTabularClass t1(&db, "t1");
  CommonTabularClass t2(&db, "t2");
  CommonTabularClass v1(&db, "v1", true);
  
  // test normal table
  CPPUNIT_ASSERT(t1.length() == 5);
  
  // test empty table
  CPPUNIT_ASSERT(t2.length() == 0);
  
  // test view
  CPPUNIT_ASSERT(v1.length() == 3);
  
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



