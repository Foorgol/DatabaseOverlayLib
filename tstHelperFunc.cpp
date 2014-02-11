/* 
 * File:   tstInteger.cpp
 * Author: volker
 * 
 * Created on January 31, 2014, 10:29 PM
 */

#include "tstHelperFunc.h"
#include "../qt4/QtCore/qvariant.h"

#include <QVariantList>
#include <QStringList>
#include <qt/QtCore/qmetatype.h>
#include <qt/QtCore/qstringlist.h>
#include <qt/QtCore/qjsonarray.h>

using namespace dbOverlay;

void tstHelperFunc::testCommaSepList()
{
  printStartMsg("testCommaSepList");
  QVariantList qvl;
  
  // test empty list
  CPPUNIT_ASSERT(commaSepStringFromList(qvl) == "");
  
  // test list with various members
  qvl << "string" << 42 << 4.2;
  CPPUNIT_ASSERT(commaSepStringFromList(qvl) == "string, 42, 4.2");
  
  // test list with two empty members in between
  qvl << "" << QVariant::Int << 88;
  CPPUNIT_ASSERT(commaSepStringFromList(qvl) == "string, 42, 4.2, , 88");
  
  // test list with an empty member at the end
  qvl << QVariant::Int;
  CPPUNIT_ASSERT(commaSepStringFromList(qvl) == "string, 42, 4.2, , 88");
  qvl << "";
  CPPUNIT_ASSERT(commaSepStringFromList(qvl) == "string, 42, 4.2, , 88, ");
  
  // test a list with an empty member at the beginning
  qvl.clear();
  CPPUNIT_ASSERT(commaSepStringFromList(qvl) == "");
  qvl << QVariant::Int;
  CPPUNIT_ASSERT(commaSepStringFromList(qvl) == "");
  qvl << "";
  CPPUNIT_ASSERT(commaSepStringFromList(qvl) == "");
  qvl << "88";
  CPPUNIT_ASSERT(commaSepStringFromList(qvl) == ", 88");
  
  // test function call with string list
  QStringList qsl;
  qsl << "" << "a"  << "b" << "";
  CPPUNIT_ASSERT(commaSepStringFromList(qsl) == ", a, b, ");
  
  printEndMsg();
}

//----------------------------------------------------------------------------

  void tstHelperFunc::testPrepWhereClause()
  {
    printStartMsg("testPrepWhereClause");
    
    // empty parameter
    QVariantList qvl;
    QVariantList result = prepWhereClause(qvl);
    CPPUNIT_ASSERT(result.length() == 1);
    CPPUNIT_ASSERT(result.at(0).toString() == "");
    
    // odd number of args
    qvl.clear();
    qvl << "a" << "b" << "c";
    CPPUNIT_ASSERT_THROW(result = prepWhereClause(qvl), std::invalid_argument);
    
    // one parameter
    qvl.clear();
    qvl << "a" << 42;
    result = prepWhereClause(qvl);
    CPPUNIT_ASSERT(result.length() == 2);
    CPPUNIT_ASSERT(result.at(0).toString() == "a = ?");
    CPPUNIT_ASSERT(result.at(1).toInt() == 42);
    
    // two args
    qvl.clear();
    qvl << "a" << 42;
    qvl << "b" << "ABC";
    result = prepWhereClause(qvl);
    CPPUNIT_ASSERT(result.length() == 3);
    CPPUNIT_ASSERT(result.at(0).toString() == "a = ? AND b = ?");
    CPPUNIT_ASSERT(result.at(1).toInt() == 42);
    CPPUNIT_ASSERT(result.at(2).toString() == "ABC");
    
    // two args incl. NULL
    qvl.clear();
    qvl << "a" << 42;
    qvl << "b" << QVariant::Int;
    result = prepWhereClause(qvl);
    CPPUNIT_ASSERT(result.length() == 2);
    CPPUNIT_ASSERT(result.at(0).toString() == "a = ? AND b IS NULL");
    CPPUNIT_ASSERT(result.at(1).toInt() == 42);
    
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
