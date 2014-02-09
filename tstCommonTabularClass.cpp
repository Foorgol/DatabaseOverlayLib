/* 
 * File:   tstGenericDatabase.cpp
 * Author: volker
 * 
 * Created on February 2, 2014, 1:02 PM
 */

#include "tstCommonTabularClass.h"
#include "dbExceptions.h"
#include "../qt4/QtCore/qchar.h"

#include <stdexcept>

#include <QList>
#include <qt/QtCore/qstringlist.h>
#include <qt/QtCore/qmetatype.h>

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



