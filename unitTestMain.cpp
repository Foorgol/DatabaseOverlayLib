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
