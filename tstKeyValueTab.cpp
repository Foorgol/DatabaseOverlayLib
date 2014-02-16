/* 
 * File:   tstGenericDatabase.cpp
 * Author: volker
 * 
 * Created on February 2, 2014, 1:02 PM
 */

#include "tstKeyValueTab.h"

#include <stdexcept>

using namespace dbOverlay;

void tstKeyValueTab::testConstructor()
{
  printStartMsg("testConstructor");
  
  SampleDB db = getScenario01(dbOverlay::GenericDatabase::SQLITE);
  
  // create a new table from scratch
  CPPUNIT_ASSERT(!(db.hasTable("kvt")));
  KeyValueTab kvt = KeyValueTab::getTab(&db, "kvt");
  CPPUNIT_ASSERT(db.hasTable("kvt"));
  DbTab t = db["kvt"];
  CPPUNIT_ASSERT(t.hasColumn("K"));
  CPPUNIT_ASSERT(t.hasColumn("V"));
  
  // try to create instance from invalid table
  CPPUNIT_ASSERT_THROW(KeyValueTab::getTab(&db, "t1"), std::invalid_argument);
  
  // try to create table from existing, valid table
  kvt = KeyValueTab::getTab(&db, "kvt");
  
  printEndMsg();
  
}

//----------------------------------------------------------------------------

void tstKeyValueTab::testGetSet()
{
  printStartMsg("testGetSet");
  
  SampleDB db = getScenario01(dbOverlay::GenericDatabase::SQLITE);
  
  // create a new table from scratch
  CPPUNIT_ASSERT(!(db.hasTable("kvt")));
  KeyValueTab kvt = KeyValueTab::getTab(&db, "kvt");
  CPPUNIT_ASSERT(db.hasTable("kvt"));
  DbTab t = db["kvt"];
  CPPUNIT_ASSERT(t.length() == 0);
  
  // get / set / update string
  kvt.set("s", "abc");
  CPPUNIT_ASSERT(t.length() == 1);
  CPPUNIT_ASSERT(kvt["s"] == "abc");
  CPPUNIT_ASSERT(kvt.getString("s") == "abc");
  kvt.set("s", "xyz");
  CPPUNIT_ASSERT(t.length() == 1);
  CPPUNIT_ASSERT(kvt["s"] == "xyz");
  CPPUNIT_ASSERT(kvt.getString("s") == "xyz");
  
  // get / set / update int
  kvt.set("i", -666);
  CPPUNIT_ASSERT(t.length() == 2);
  CPPUNIT_ASSERT(kvt["i"] == "-666");
  CPPUNIT_ASSERT(kvt["i"].toInt() == -666);
  CPPUNIT_ASSERT(kvt.getInt("i") == -666);
  kvt.set("i", 4242);
  CPPUNIT_ASSERT(t.length() == 2);
  CPPUNIT_ASSERT(kvt["i"] == "4242");
  CPPUNIT_ASSERT(kvt["i"].toInt() == 4242);
  CPPUNIT_ASSERT(kvt.getInt("i") == 4242);
  
  // get / set / update bool
  kvt.set("b", true);
  CPPUNIT_ASSERT(t.length() == 3);
  CPPUNIT_ASSERT(kvt["b"] == "1");
  CPPUNIT_ASSERT(kvt["b"].toBool() == true);
  CPPUNIT_ASSERT(kvt.getBool("b") == true);
  kvt.set("b", false);
  CPPUNIT_ASSERT(t.length() == 3);
  CPPUNIT_ASSERT(kvt["b"] == "0");
  CPPUNIT_ASSERT(kvt["b"].toBool() == false);
  CPPUNIT_ASSERT(kvt.getBool("b") == false);
  
  // get / set / update double
  kvt.set("d", -3.1415);
  CPPUNIT_ASSERT(t.length() == 4);
  CPPUNIT_ASSERT(kvt["d"] == "-3.1415");
  CPPUNIT_ASSERT(kvt["d"].toDouble() == -3.1415);
  CPPUNIT_ASSERT(kvt.getDouble("d") == -3.1415);
  kvt.set("d", 42.42);
  CPPUNIT_ASSERT(t.length() == 4);
  CPPUNIT_ASSERT(kvt["d"] == "42.42");
  CPPUNIT_ASSERT(kvt["d"].toDouble() == 42.42);
  CPPUNIT_ASSERT(kvt.getDouble("d") == 42.42);
  
  // get / set / update NULL
  kvt.set("n", QVariant::Int);
  CPPUNIT_ASSERT(t.length() == 5);
  CPPUNIT_ASSERT(kvt["n"].isNull());
  kvt.set("n", 42.42);
  CPPUNIT_ASSERT(t.length() == 5);
  CPPUNIT_ASSERT(kvt["d"] == "42.42");
  CPPUNIT_ASSERT(kvt["d"].toDouble() == 42.42);
  CPPUNIT_ASSERT(kvt.getDouble("d") == 42.42);
  
  // get non-existing value
  CPPUNIT_ASSERT(!(kvt["dkjfdf"].isValid()));
  
  
  printEndMsg();  
}

//----------------------------------------------------------------------------


//----------------------------------------------------------------------------


//----------------------------------------------------------------------------


//----------------------------------------------------------------------------


//----------------------------------------------------------------------------


//----------------------------------------------------------------------------


//----------------------------------------------------------------------------


//----------------------------------------------------------------------------


//----------------------------------------------------------------------------


//----------------------------------------------------------------------------


//----------------------------------------------------------------------------


//----------------------------------------------------------------------------


//----------------------------------------------------------------------------


//----------------------------------------------------------------------------


//----------------------------------------------------------------------------


//----------------------------------------------------------------------------



