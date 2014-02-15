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
  CPPUNIT_TEST(testGetColType);
  CPPUNIT_TEST(testcid2name);
  CPPUNIT_TEST(testname2cid);
  CPPUNIT_TEST(testHasColumn);
  CPPUNIT_TEST(testGetMatchCountForWhereClause);
  CPPUNIT_TEST(testGetMatchCountForColumnValue);
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
    void testGetColType();
    void testcid2name();
    void testname2cid();
    void testHasColumn();
    void testGetMatchCountForWhereClause();
    void testGetMatchCountForColumnValue();
};

#endif	/* TSTGENERICDATABASE_H */

