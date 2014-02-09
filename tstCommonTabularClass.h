/* 
 * File:   tstGenericDatabase.h
 * Author: volker
 *
 * Created on February 2, 2014, 1:02 PM
 */

#ifndef TSTCOMMONTABULARCLASS_H
#define	TSTCOMMONTABULARCLASS_H

#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "BasicTestClass.h"
#include "CommonTabularClass.h"
#include "SampleDB.h"
#include "DatabaseTestScenario.h"

class tstCommonTabularClass : public DatabaseTestScenario {
  CPPUNIT_TEST_SUITE( tstCommonTabularClass );
  CPPUNIT_TEST(testConstructor);
  CPPUNIT_TEST(testAllColDefs);
//  CPPUNIT_TEST();
//  CPPUNIT_TEST();
//  CPPUNIT_TEST();
//  CPPUNIT_TEST();
//  CPPUNIT_TEST();
//  CPPUNIT_TEST();
//  CPPUNIT_TEST();
//  CPPUNIT_TEST();
//  CPPUNIT_TEST();
//  CPPUNIT_TEST();
//  CPPUNIT_TEST();
//  CPPUNIT_TEST();
//  CPPUNIT_TEST();
//  CPPUNIT_TEST();
  CPPUNIT_TEST_SUITE_END();
  
public:
    void testConstructor();
    void testAllColDefs();
};

#endif	/* TSTGENERICDATABASE_H */

