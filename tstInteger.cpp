/* 
 * File:   tstInteger.cpp
 * Author: volker
 * 
 * Created on January 31, 2014, 10:29 PM
 */

#include "tstInteger.h"
#include "dbExceptions.h"

using namespace dbOverlay;

void tstInteger::testConstructor()
{
    Integer empty;
    
    CPPUNIT_ASSERT(empty.hasValue() == false);
    CPPUNIT_ASSERT_THROW(empty.getValue(), dbOverlay::ObjectEmptyException);
    
    Integer i1(42);
    CPPUNIT_ASSERT(i1.hasValue() == true);
    CPPUNIT_ASSERT(i1.getValue() == 42);
    
    Integer i2(i1);
    CPPUNIT_ASSERT(i2.hasValue() == true);
    CPPUNIT_ASSERT(i2.getValue() == 42);
    i1.setValue(23);
    CPPUNIT_ASSERT(i2.hasValue() == true);
    CPPUNIT_ASSERT(i2.getValue() == 42);
    CPPUNIT_ASSERT(i1.hasValue() == true);
    CPPUNIT_ASSERT(i1.getValue() == 23);
}

void tstInteger::testSet()
{
    Integer i;
    
    CPPUNIT_ASSERT(i.hasValue() == false);
    CPPUNIT_ASSERT_THROW(i.getValue(), dbOverlay::ObjectEmptyException);
    
    i.setValue(88);
    CPPUNIT_ASSERT(i.hasValue() == true);
    CPPUNIT_ASSERT(i.getValue() == 88);
}