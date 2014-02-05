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
  CPPUNIT_TEST_SUITE_END();
  
public:
    void testConstructorMySql();
    void testConstructorSQLite();
    void testPopulate();
    

};

#endif	/* TSTGENERICDATABASE_H */

