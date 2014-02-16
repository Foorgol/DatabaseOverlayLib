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

#ifndef TSTINTEGER_H
#define	TSTINTEGER_H

#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "BasicTestClass.h"
#include "Integer.h"

class tstInteger : public BasicTestClass {
  CPPUNIT_TEST_SUITE( tstInteger );
  CPPUNIT_TEST( testConstructor );
  CPPUNIT_TEST( testSet );
  CPPUNIT_TEST_SUITE_END();
  
public:
    void testConstructor();
    void testSet();

};

#endif	/* TSTINTEGER_H */

