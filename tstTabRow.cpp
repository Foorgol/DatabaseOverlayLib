/* 
 * File:   tstGenericDatabase.cpp
 * Author: volker
 * 
 * Created on February 2, 2014, 1:02 PM
 */

#include "tstTabRow.h"
#include "dbExceptions.h"
#include "TabRow.h"

#include <stdexcept>

#include <QList>
#include <qt/QtCore/qstringlist.h>
#include <qt/QtCore/qmetatype.h>
#include <qt/QtCore/qjsonarray.h>

using namespace dbOverlay;

void tstTabRow::testConstructor()
{
  printStartMsg("testConstructor");
  
  SampleDB db = getScenario01(dbOverlay::GenericDatabase::SQLITE);
  
  
  //
  // Basic case: table name and ID
  //
  
  // invalid parameters
  CPPUNIT_ASSERT_THROW(TabRow r(NULL, "t1", 1), EmptyDatabaseHandleException);
  CPPUNIT_ASSERT_THROW(TabRow r(&db, "xxx", 1), InvalidTabNameException);
  CPPUNIT_ASSERT_THROW(TabRow r(&db, "t1", 100), InvalidRowQualifierException);
  
  // valid parameters
  TabRow r(&db, "t1", 2);
  CPPUNIT_ASSERT_EQUAL(2, r.getId());
  
  
  //
  // Extended case, part 1: column/value-pairs to be ANDed
  //
  
  // only one column
  QVariantList cvp;
  cvp << "i" << 84;
  r = TabRow(&db, "t1", cvp);
  CPPUNIT_ASSERT_EQUAL(3, r.getId());
  
  // two columns
  cvp = QVariantList();
  cvp << "i" << 84;
  cvp << "f" << 42.42;
  r = TabRow(&db, "t1", cvp);
  CPPUNIT_ASSERT_EQUAL(5, r.getId());
    
  // column with NULL value
  cvp = QVariantList();
  cvp << "i" << QVariant::Int;
  r = TabRow(&db, "t1", cvp);
  CPPUNIT_ASSERT_EQUAL(2, r.getId());
  
  // NULL value combined with normal value
  cvp = QVariantList();
  cvp << "f" << QVariant::Int;
  cvp << "s" << "Hoi";
  r = TabRow(&db, "t1", cvp);
  CPPUNIT_ASSERT_EQUAL(4, r.getId());
  
  // Criteria that yield no match
  cvp = QVariantList();
  cvp << "i" << 840;
  CPPUNIT_ASSERT_THROW(r = TabRow(&db, "t1", cvp), InvalidRowQualifierException);
  
  // Odd number of args
  cvp = QVariantList();
  cvp << "i" << 84;
  cvp << "qqqq";
  CPPUNIT_ASSERT_THROW(r = TabRow(&db, "t1", cvp), std::invalid_argument);

  // non-existing column name
  cvp = QVariantList();
  cvp << "xxx" << 84;
  CPPUNIT_ASSERT_THROW(r = TabRow(&db, "t1", cvp), InvalidRowQualifierException);
  
  // empty column name
  cvp = QVariantList();
  cvp << "" << 84;
  CPPUNIT_ASSERT_THROW(r = TabRow(&db, "t1", cvp), InvalidRowQualifierException);
  cvp = QVariantList();
  cvp << QVariant::Int << 84;
  CPPUNIT_ASSERT_THROW(r = TabRow(&db, "t1", cvp), InvalidRowQualifierException);
  
  //
  // Extended case, part 2: WHERE clause explicitly provided
  //
  
  // valid request, one parameter
  cvp = QVariantList();
  cvp << "id = ?" << 2;
  r = TabRow(&db, "t1", cvp);
  CPPUNIT_ASSERT_EQUAL(2, r.getId());
  
  // valid request, two parameters
  cvp = QVariantList();
  cvp << "i > ? AND s = ?" << 50 << "Hoi";
  r = TabRow(&db, "t1", cvp);
  CPPUNIT_ASSERT_EQUAL(4, r.getId());
  
  // valid request that yields no result
  cvp = QVariantList();
  cvp << "i > ? AND s = ?" << 500 << "Hoi";
  CPPUNIT_ASSERT_THROW(r = TabRow(&db, "t1", cvp), InvalidRowQualifierException);
  
  // invalid requests
  cvp = QVariantList();
  cvp << "ldkjf ldsjfsd lkdjfsdf" << 500 << "Hoi";
  CPPUNIT_ASSERT_THROW(r = TabRow(&db, "t1", cvp), InvalidRowQualifierException);
  cvp = QVariantList();
  cvp << "ldkjf ldsjfsd lkdjfsdf";
  CPPUNIT_ASSERT_THROW(r = TabRow(&db, "t1", cvp), InvalidRowQualifierException);
  
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



