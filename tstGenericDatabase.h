/* 
 * File:   tstGenericDatabase.h
 * Author: volker
 *
 * Created on February 2, 2014, 1:02 PM
 */

#ifndef TSTGENERICDATABASE_H
#define	TSTGENERICDATABASE_H

#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "BasicTestClass.h"
#include "GenericDatabase.h"
#include "SampleDB.h"
#include "DatabaseTestScenario.h"

class tstGenericDatabase : public DatabaseTestScenario {
  CPPUNIT_TEST_SUITE( tstGenericDatabase );
  CPPUNIT_TEST( testConstructorMySql );
  CPPUNIT_TEST( testConstructorSQLite );
  CPPUNIT_TEST( testPopulate );
  CPPUNIT_TEST( testGetTableNames );
  CPPUNIT_TEST( testHasTable );
  CPPUNIT_TEST(testExecScalarQuery);
  CPPUNIT_TEST(testExecContentQuery);
  CPPUNIT_TEST(testGetTab);
//  CPPUNIT_TEST();
//  CPPUNIT_TEST();
//  CPPUNIT_TEST();
//  CPPUNIT_TEST();
  CPPUNIT_TEST_SUITE_END();
  
public:
    void testConstructorMySql();
    void testConstructorSQLite();
    void testPopulate();
    void testGetTableNames();
    void testHasTable();
    void testExecScalarQuery();
    void testExecContentQuery();
    void testGetTab();
};

#endif	/* TSTGENERICDATABASE_H */

