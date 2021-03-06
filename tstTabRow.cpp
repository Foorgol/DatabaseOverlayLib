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

#include "tstTabRow.h"
#include "dbExceptions.h"
#include "TabRow.h"
#include "DbTab.h"

#include <stdexcept>

#include <QList>
#include <qt/QtCore/qstringlist.h>
#include <qt/QtCore/qmetatype.h>
#include <qt/QtCore/qjsonarray.h>

using namespace dbOverlay;

void tstTabRow::testConstructor()
{
  printStartMsg("testConstructor");
  
  SampleDB db = getScenario01(dbOverlay::GenericDatabase::SQLITE);
  
  
  //
  // Basic case: table name and ID
  //
  
  // invalid parameters
  CPPUNIT_ASSERT_THROW(TabRow r(NULL, "t1", 1), EmptyDatabaseHandleException);
  CPPUNIT_ASSERT_THROW(TabRow r(&db, "xxx", 1), InvalidTabNameException);
  CPPUNIT_ASSERT_THROW(TabRow r(&db, "t1", 100), InvalidRowQualifierException);
  
  // valid parameters
  TabRow r(&db, "t1", 2);
  CPPUNIT_ASSERT_EQUAL(2, r.getId());
  
  
  //
  // Extended case, part 1: column/value-pairs to be ANDed
  //
  
  // only one column
  QVariantList cvp;
  cvp << "i" << 84;
  r = TabRow(&db, "t1", cvp);
  CPPUNIT_ASSERT_EQUAL(3, r.getId());
  
  // two columns
  cvp = QVariantList();
  cvp << "i" << 84;
  cvp << "f" << 42.42;
  r = TabRow(&db, "t1", cvp);
  CPPUNIT_ASSERT_EQUAL(5, r.getId());
    
  // column with NULL value
  cvp = QVariantList();
  cvp << "i" << QVariant::Int;
  r = TabRow(&db, "t1", cvp);
  CPPUNIT_ASSERT_EQUAL(2, r.getId());
  
  // NULL value combined with normal value
  cvp = QVariantList();
  cvp << "f" << QVariant::Int;
  cvp << "s" << "Hoi";
  r = TabRow(&db, "t1", cvp);
  CPPUNIT_ASSERT_EQUAL(4, r.getId());
  
  // Criteria that yield no match
  cvp = QVariantList();
  cvp << "i" << 840;
  CPPUNIT_ASSERT_THROW(r = TabRow(&db, "t1", cvp), InvalidRowQualifierException);
  
  // Odd number of args
  cvp = QVariantList();
  cvp << "i" << 84;
  cvp << "qqqq";
  CPPUNIT_ASSERT_THROW(r = TabRow(&db, "t1", cvp), std::invalid_argument);

  // non-existing column name
  cvp = QVariantList();
  cvp << "xxx" << 84;
  CPPUNIT_ASSERT_THROW(r = TabRow(&db, "t1", cvp), InvalidRowQualifierException);
  
  // empty column name
  cvp = QVariantList();
  cvp << "" << 84;
  CPPUNIT_ASSERT_THROW(r = TabRow(&db, "t1", cvp), InvalidRowQualifierException);
  cvp = QVariantList();
  cvp << QVariant::Int << 84;
  CPPUNIT_ASSERT_THROW(r = TabRow(&db, "t1", cvp), InvalidRowQualifierException);
  
  //
  // Extended case, part 2: WHERE clause explicitly provided
  //
  
  // valid request, one parameter
  cvp = QVariantList();
  cvp << "id = ?" << 2;
  r = TabRow(&db, "t1", cvp);
  CPPUNIT_ASSERT_EQUAL(2, r.getId());
  
  // valid request, two parameters
  cvp = QVariantList();
  cvp << "i > ? AND s = ?" << 50 << "Hoi";
  r = TabRow(&db, "t1", cvp);
  CPPUNIT_ASSERT_EQUAL(4, r.getId());
  
  // valid request that yields no result
  cvp = QVariantList();
  cvp << "i > ? AND s = ?" << 500 << "Hoi";
  CPPUNIT_ASSERT_THROW(r = TabRow(&db, "t1", cvp), InvalidRowQualifierException);
  
  // invalid requests
  cvp = QVariantList();
  cvp << "ldkjf ldsjfsd lkdjfsdf" << 500 << "Hoi";
  CPPUNIT_ASSERT_THROW(r = TabRow(&db, "t1", cvp), InvalidRowQualifierException);
  cvp = QVariantList();
  cvp << "ldkjf ldsjfsd lkdjfsdf";
  CPPUNIT_ASSERT_THROW(r = TabRow(&db, "t1", cvp), InvalidRowQualifierException);
  
  printEndMsg();
  
}

//----------------------------------------------------------------------------

void tstTabRow::testUpdate()
{
  printStartMsg("testUpdate");

  QList<dbOverlay::GenericDatabase::DB_ENGINE> dbTypes;
  dbTypes.append(dbOverlay::GenericDatabase::SQLITE);
  dbTypes.append(dbOverlay::GenericDatabase::MYSQL);

  QList<dbOverlay::GenericDatabase::DB_ENGINE>::iterator i;
  for (i = dbTypes.begin(); i != dbTypes.end(); ++i)
  {
    SampleDB db = getScenario01(*i);
    QSqlDatabase check = getDbConn(*i);
    TabRow r(&db, "t1", 2);
    
    QVariantList qvl;
    
    // regular update
    qvl << "i" << 666;
    CPPUNIT_ASSERT(r.update(qvl));
    QSqlQuery q = check.exec("SELECT * FROM t1 WHERE id=2");
    CPPUNIT_ASSERT(q.first());
    CPPUNIT_ASSERT(q.value(0).toInt() == 2);
    CPPUNIT_ASSERT(q.value(1).toInt() == 666);
    CPPUNIT_ASSERT(q.value(2).toDouble() == 666.66);
    CPPUNIT_ASSERT(q.value(3).toString() == "Hi");
    q.clear();
    
    // update more than one column, including NULL values
    qvl.clear();
    qvl << "i" << QVariant::Int;
    qvl << "s" << ",,,";
    CPPUNIT_ASSERT(r.update(qvl));
    q = check.exec("SELECT * FROM t1 WHERE id=2");
    CPPUNIT_ASSERT(q.first());
    CPPUNIT_ASSERT(q.value(0).toInt() == 2);
    CPPUNIT_ASSERT(q.value(1).isNull());
    CPPUNIT_ASSERT(q.value(2).toDouble() == 666.66);
    CPPUNIT_ASSERT(q.value(3).toString() == ",,,");
    q.clear();
    
    // try to update the id column
    qvl.clear();
    qvl << "id" << 666;
    qvl << "i" << -5;
    qvl << "f" << -5.55;
    qvl << "s" << "Noooo";
    CPPUNIT_ASSERT_THROW(r.update(qvl), std::invalid_argument);
    q = check.exec("SELECT * FROM t1 WHERE id=2");
    CPPUNIT_ASSERT(q.first());
    CPPUNIT_ASSERT(q.value(0).toInt() == 2);
    CPPUNIT_ASSERT(q.value(1).isNull());
    CPPUNIT_ASSERT(q.value(2).toDouble() == 666.66);
    CPPUNIT_ASSERT(q.value(3).toString() == ",,,");
    q.clear();
    
    // invalid number of args
    qvl.clear();
    qvl << "i" << -5;
    qvl << "f" << -5.55;
    qvl << "s";
    CPPUNIT_ASSERT_THROW(r.update(qvl), std::invalid_argument);
    q = check.exec("SELECT * FROM t1 WHERE id=2");
    CPPUNIT_ASSERT(q.first());
    CPPUNIT_ASSERT(q.value(0).toInt() == 2);
    CPPUNIT_ASSERT(q.value(1).isNull());
    CPPUNIT_ASSERT(q.value(2).toDouble() == 666.66);
    CPPUNIT_ASSERT(q.value(3).toString() == ",,,");
    q.clear();
    
    // invalid column names
    qvl.clear();
    qvl << "x" << -5;
    qvl << "y" << -5.55;
    qvl << "z" << "qqq";
    CPPUNIT_ASSERT(!(r.update(qvl)));
    q = check.exec("SELECT * FROM t1 WHERE id=2");
    CPPUNIT_ASSERT(q.first());
    CPPUNIT_ASSERT(q.value(0).toInt() == 2);
    CPPUNIT_ASSERT(q.value(1).isNull());
    CPPUNIT_ASSERT(q.value(2).toDouble() == 666.66);
    CPPUNIT_ASSERT(q.value(3).toString() == ",,,");
    q.clear();
    
    // remove the connection of the "Object under test"
    db.close();

    // remove the connection of the unittest framework
    removeDbConn();
  }
  
  printEndMsg();
}
//----------------------------------------------------------------------------

void tstTabRow::testColumnAccess()
{
  printStartMsg("testColumnAccess");

  SampleDB db = getScenario01(dbOverlay::GenericDatabase::SQLITE);
  TabRow r = db["t1"][5];
  
  // regular look-up
  CPPUNIT_ASSERT(r["id"].toInt() == 5);
  CPPUNIT_ASSERT(r["i"].toInt() == 84);
  CPPUNIT_ASSERT(r["f"].toDouble() == 42.42);
  CPPUNIT_ASSERT(r["s"].toString() == "Ho");
  
  // invalid column names
  CPPUNIT_ASSERT_THROW(r[""], std::invalid_argument);
  CPPUNIT_ASSERT_THROW(r[QString::null], std::invalid_argument);
  CPPUNIT_ASSERT_THROW(r["xxx"], std::invalid_argument);
  
  printEndMsg();
}

//----------------------------------------------------------------------------

void tstTabRow::testErase()
{
  printStartMsg("testErase");

  SampleDB db = getScenario01(dbOverlay::GenericDatabase::SQLITE);
  TabRow r = db["t1"][3];
  
  // test number of entries before and after delete
  CPPUNIT_ASSERT(db["t1"].length() == 5);
  CPPUNIT_ASSERT(r.erase());
  CPPUNIT_ASSERT(db["t1"].length() == 4);
  
  // make sure the ID is invalid
  CPPUNIT_ASSERT(r.getId() < 0);
  
  // make sure the row with ID 3 doesn't exist anymore
  CPPUNIT_ASSERT_THROW(r = db["t1"][3], InvalidRowQualifierException);
  
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


//----------------------------------------------------------------------------



