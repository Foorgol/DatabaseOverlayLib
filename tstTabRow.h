/* 
 * File:   tstGenericDatabase.h
 * Author: volker
 *
 * Created on February 2, 2014, 1:02 PM
 */

#ifndef TSTTABROW_H
#define	TSTTABROW_H

#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "BasicTestClass.h"
#include "GenericDatabase.h"
#include "SampleDB.h"
#include "DatabaseTestScenario.h"

class tstTabRow : public DatabaseTestScenario {
  CPPUNIT_TEST_SUITE( tstTabRow );
  CPPUNIT_TEST(testConstructor);
  CPPUNIT_TEST(testUpdate);
  CPPUNIT_TEST(testColumnAccess);
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
    void testUpdate();
    void testColumnAccess();
};

#endif	/* TSTGENERICDATABASE_H */

