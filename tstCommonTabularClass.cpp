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



