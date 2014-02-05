/* 
 * File:   tstInteger.cpp
 * Author: volker
 * 
 * Created on January 31, 2014, 10:29 PM
 */

#include "tstHelperFunc.h"
#include "../qt4/QtCore/qvariant.h"

#include <QVariantList>
#include <qt/QtCore/qmetatype.h>

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
  
  printEndMsg();
}