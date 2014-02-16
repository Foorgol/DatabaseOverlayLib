/* 
 * File:   tstGenericDatabase.h
 * Author: volker
 *
 * Created on February 2, 2014, 1:02 PM
 */

#ifndef TSTDBTAB_H
#define	TSTDBTAB_H

#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "DbTab.h"
#include "SampleDB.h"
#include "DatabaseTestScenario.h"

class tstDbTab : public DatabaseTestScenario {
  CPPUNIT_TEST_SUITE( tstDbTab );
  CPPUNIT_TEST(testInsert);
  CPPUNIT_TEST(testIterator);
  CPPUNIT_TEST(testGetRowsByWhereClause);
  CPPUNIT_TEST(testGetRowsByColumnValue);
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
    void testInsert();
    void testIterator();
    void testGetRowsByWhereClause();
    void testGetRowsByColumnValue();
};

#endif	/* TSTGENERICDATABASE_H */

