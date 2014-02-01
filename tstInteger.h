/* 
 * File:   tstInteger.h
 * Author: volker
 *
 * Created on January 31, 2014, 10:29 PM
 */

#ifndef TSTINTEGER_H
#define	TSTINTEGER_H

#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "Integer.h"

class tstInteger : public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE( tstInteger );
  CPPUNIT_TEST( testConstructor );
  CPPUNIT_TEST_SUITE_END();
  
public:
    void setUp() {}
    void tearDown() {}
    
    void testConstructor();

};

#endif	/* TSTINTEGER_H */

