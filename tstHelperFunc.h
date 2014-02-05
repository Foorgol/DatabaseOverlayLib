/* 
 * File:   tstInteger.h
 * Author: volker
 *
 * Created on January 31, 2014, 10:29 PM
 */

#ifndef TSTHELPERFUNC_H
#define	TSTHELPERFUNC_H

#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "BasicTestClass.h"
#include "HelperFunc.h"

class tstHelperFunc : public BasicTestClass {
  CPPUNIT_TEST_SUITE( tstHelperFunc );
  CPPUNIT_TEST( testCommaSepList );
  CPPUNIT_TEST_SUITE_END();
  
public:
    void testCommaSepList();

};

#endif	/* TSTHELPERFUNC_H */

