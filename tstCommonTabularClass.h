/*
 * Copyright © 2014 Volker Knollmann
 * 
 * This work is free. You can redistribute it and/or modify it under the
 * terms of the Do What The Fuck You Want To Public License, Version 2,
 * as published by Sam Hocevar. See the COPYING file or visit
 * http://www.wtfpl.net/ for more details.
 * 
 * This program comes without any warranty. Use it at your own risk or
 * don't use it at all.
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
  CPPUNIT_TEST(testGetLength);
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
    void testGetLength();
};

#endif	/* TSTGENERICDATABASE_H */

