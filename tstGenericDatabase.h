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

