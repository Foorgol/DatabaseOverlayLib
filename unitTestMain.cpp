/* 
 * File:   unitTestMain.cpp
 * Author: volker
 *
 * Created on January 31, 2014, 10:27 PM
 */

#include <cstdlib>
#include <QApplication>
#include <cppunit/TestSuite.h>
#include <cppunit/ui/text/TestRunner.h>

#include "tstInteger.h"
#include "tstGenericDatabase.h"
#include "tstHelperFunc.h"
#include "tstCommonTabularClass.h"
#include "tstTabRow.h"
#include "tstDbTab.h"

// comment / uncomment the following to execute just one suite
#define TEST_ALL_SUITES

// Registers the fixture into the 'registry'
#ifdef TEST_ALL_SUITES
  CPPUNIT_TEST_SUITE_REGISTRATION( tstInteger );
  CPPUNIT_TEST_SUITE_REGISTRATION(tstGenericDatabase);
  CPPUNIT_TEST_SUITE_REGISTRATION(tstHelperFunc);
  CPPUNIT_TEST_SUITE_REGISTRATION(tstCommonTabularClass);
  CPPUNIT_TEST_SUITE_REGISTRATION(tstTabRow);
  CPPUNIT_TEST_SUITE_REGISTRATION(tstDbTab);
#else
  CPPUNIT_TEST_SUITE_REGISTRATION(tstCommonTabularClass);
#endif


int main(int argc, char *argv[]) {
    // initialize resources, if needed
    // Q_INIT_RESOURCE(resfile);

    QApplication app(argc, argv);
    
    CppUnit::TextUi::TestRunner runner;
    CppUnit::Test *suite;
    
    suite = CppUnit::TestFactoryRegistry::getRegistry().makeTest();
    
    runner.addTest(suite);
    
    runner.run();
    
}
