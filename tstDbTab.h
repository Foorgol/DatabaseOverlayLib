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
  CPPUNIT_TEST(testGetAllRows);
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
    void testGetAllRows();
};

#endif	/* TSTGENERICDATABASE_H */

