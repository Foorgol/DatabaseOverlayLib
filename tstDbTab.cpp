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

#include "tstDbTab.h"
#include "dbExceptions.h"

#include <stdexcept>

#include <QList>
#include <qt/QtCore/qstringlist.h>
#include <qt/QtCore/qmetatype.h>
#include <qt/QtCore/qjsonarray.h>

using namespace dbOverlay;

void tstDbTab::testInsert()
{
  printStartMsg("testInsert");

  QList<dbOverlay::GenericDatabase::DB_ENGINE> dbTypes;
  dbTypes.append(dbOverlay::GenericDatabase::SQLITE);
  dbTypes.append(dbOverlay::GenericDatabase::MYSQL);

  QList<dbOverlay::GenericDatabase::DB_ENGINE>::iterator i;
  for (i = dbTypes.begin(); i != dbTypes.end(); ++i)
  {
    SampleDB db = getScenario01(*i);
    QSqlDatabase check = getDbConn(*i);

    int newId;
    DbTab t = db["t1"];
    QVariantList qvl;

    // test normal insert
    qvl << "i" << 666;
    qvl << "f" << 77.88;
    qvl << "s" << "abc";
    newId = t.insertRow(qvl);
    CPPUNIT_ASSERT(newId == 6);
    QSqlQuery q = check.exec("SELECT * FROM t1 WHERE id=6");
    CPPUNIT_ASSERT(q.first());
    CPPUNIT_ASSERT(q.value(0).toInt() == 6);
    CPPUNIT_ASSERT(q.value(1).toInt() == 666);
    CPPUNIT_ASSERT(q.value(2).toDouble() == 77.88);
    CPPUNIT_ASSERT(q.value(3).toString() == "abc");
    q.clear();

    // test insert of NULLs
    qvl.clear();
    qvl << "i" << QVariant::Int;
    qvl << "f" << QVariant::Int;
    qvl << "s" << QVariant::Int;
    newId = t.insertRow(qvl);
    CPPUNIT_ASSERT(newId == 7);
    q = check.exec("SELECT * FROM t1 WHERE id=7");
    CPPUNIT_ASSERT(q.first());
    CPPUNIT_ASSERT(q.value(0).toInt() == 7);
    CPPUNIT_ASSERT(q.value(1).isNull());
    CPPUNIT_ASSERT(q.value(2).isNull());
    CPPUNIT_ASSERT(q.value(3).isNull());
    q.clear();

    // test insert of default values (case 1)
    qvl.clear();
    newId = t.insertRow(qvl);
    CPPUNIT_ASSERT(newId == 8);
    q = check.exec("SELECT * FROM t1 WHERE id=8");
    CPPUNIT_ASSERT(q.first());
    CPPUNIT_ASSERT(q.value(0).toInt() == 8);
    CPPUNIT_ASSERT(q.value(1).isNull());
    CPPUNIT_ASSERT(q.value(2).isNull());
    CPPUNIT_ASSERT(q.value(3).isNull());
    q.clear();

    // test insert of default values (case 2)
    qvl.clear();
    newId = t.insertRow();
    CPPUNIT_ASSERT(newId == 9);
    q = check.exec("SELECT * FROM t1 WHERE id=9");
    CPPUNIT_ASSERT(q.first());
    CPPUNIT_ASSERT(q.value(0).toInt() == 9);
    CPPUNIT_ASSERT(q.value(1).isNull());
    CPPUNIT_ASSERT(q.value(2).isNull());
    CPPUNIT_ASSERT(q.value(3).isNull());
    q.clear();

    // invalid number of args
    qvl.clear();
    qvl << "i" << 666;
    qvl << "f";
    CPPUNIT_ASSERT_THROW(t.insertRow(qvl), std::invalid_argument);
    q = check.exec("SELECT count(id) FROM t1");  // make sure no row has been inserted
    CPPUNIT_ASSERT(q.first());
    CPPUNIT_ASSERT(q.value(0).toInt() == 9);
    q.clear();

    // invalid column name
    qvl.clear();
    qvl << "x" << 666;
    qvl << "y" << 77.88;
    qvl << "z" << "abc";
    newId = t.insertRow(qvl);
    CPPUNIT_ASSERT(newId == -1);
    q = check.exec("SELECT count(id) FROM t1");  // make sure no row has been inserted
    CPPUNIT_ASSERT(q.first());
    CPPUNIT_ASSERT(q.value(0).toInt() == 9);
    q.clear();

    // remove the connection of the "Object under test"
    db.close();

    // remove the connection of the unittest framework
    removeDbConn();
  }
  printEndMsg();
  
}

//----------------------------------------------------------------------------

void tstDbTab::testIterator()
{
  printStartMsg("testIterator");
  
  SampleDB db = getScenario01(dbOverlay::GenericDatabase::SQLITE);
  QSqlDatabase check = getDbConn(dbOverlay::GenericDatabase::SQLITE);
  
  // test normal query
  QSqlQuery qry = check.exec("SELECT * FROM t1");
  DbTab::CachingRowIterator i(&db, "t1", qry);
  CPPUNIT_ASSERT(i.isValid());
  CPPUNIT_ASSERT(i.length() == 5);
  int idCnt = 1;
  while (!i.isEnd())
  {
    TabRow r = *i;
    CPPUNIT_ASSERT(r.getId() == idCnt);
    ++i;
    idCnt++;
  }
  CPPUNIT_ASSERT(idCnt == i.length()+1);
  
  // test query that returns no results
  qry = check.exec("SELECT * FROM t1 WHERE i > 4242");
  i = DbTab::CachingRowIterator(&db, "t1", qry);
  CPPUNIT_ASSERT(!i.isValid());
  CPPUNIT_ASSERT(i.length() == 0);
  CPPUNIT_ASSERT(i.isEnd());
  
  // test inactive query
  qry = check.exec("SELECT * FROM t1 WHERE i > 4242");
  qry.finish();
  CPPUNIT_ASSERT_THROW(i = DbTab::CachingRowIterator(&db, "t1", qry), std::invalid_argument);
  
  // test non-select query
  qry = check.exec("UPDATE t1 SET i=666 WHERE id=1");
  CPPUNIT_ASSERT_THROW(i = DbTab::CachingRowIterator(&db, "t1", qry), std::invalid_argument);
  
  printEndMsg();
}
//----------------------------------------------------------------------------

void tstDbTab::testGetRowsByWhereClause()
{
  printStartMsg("testGetRowsByWhereClause");
  
  SampleDB db = getScenario01(dbOverlay::GenericDatabase::SQLITE);
  DbTab t1 = db["t1"];
  
  // test invalid or empty where clause
  CPPUNIT_ASSERT_THROW(t1.getRowsByWhereClause(""), std::invalid_argument);
  CPPUNIT_ASSERT_THROW(t1.getRowsByWhereClause(QString::null), std::invalid_argument);
  CPPUNIT_ASSERT_THROW(t1.getRowsByWhereClause("lkdflsjflsdf"), std::invalid_argument);
  
  // test valid queries without parameters
  DbTab::CachingRowIterator i = t1.getRowsByWhereClause("i = 84");
  CPPUNIT_ASSERT(i.isValid());
  CPPUNIT_ASSERT(i.length() == 3);
  CPPUNIT_ASSERT(!i.isEnd());

  // normal query with results
  QVariantList qvl;
  qvl << "Ho";
  qvl << 50;
  i = t1.getRowsByWhereClause("s = ? AND i > ?", qvl);
  CPPUNIT_ASSERT(i.isValid());
  CPPUNIT_ASSERT(i.length() == 2);
  CPPUNIT_ASSERT(!i.isEnd());
  
  // test a query that matches zero rows
  qvl.clear();
  qvl << 5000;
  i = t1.getRowsByWhereClause("i > ?", qvl);
  CPPUNIT_ASSERT(!i.isValid());
  CPPUNIT_ASSERT(i.length() == 0);
  CPPUNIT_ASSERT(i.isEnd());
  
  // test a wrong number of parameters
  qvl.clear();
  CPPUNIT_ASSERT_THROW(t1.getRowsByWhereClause("s = ? AND i > ?", qvl), std::invalid_argument);
  
  printEndMsg();
}

//----------------------------------------------------------------------------

void tstDbTab::testGetRowsByColumnValue()
{
  printStartMsg("testGetRowsByColumnValue");

  SampleDB db = getScenario01(dbOverlay::GenericDatabase::SQLITE);
  DbTab t1 = db["t1"];
  
  // test invalid or empty arguments list
  QVariantList qvl;
  CPPUNIT_ASSERT_THROW(t1.getRowsByColumnValue(qvl), std::invalid_argument);

  qvl << "Odd number of parameters makes no sense";
  CPPUNIT_ASSERT_THROW(t1.getRowsByColumnValue(qvl), std::invalid_argument);

  qvl.clear();
  qvl << "InvalidColName";
  qvl << "42";
  CPPUNIT_ASSERT_THROW(t1.getRowsByColumnValue(qvl), std::invalid_argument);
  
  // test valid query with parameters
  qvl.clear();
  qvl << "i";
  qvl << 84;
  DbTab::CachingRowIterator i = t1.getRowsByColumnValue(qvl);
  CPPUNIT_ASSERT(i.isValid());
  CPPUNIT_ASSERT(i.length() == 3);
  CPPUNIT_ASSERT(!i.isEnd());
  
  // two parameters, ANDed, incl. NULL
  qvl.clear();
  qvl << "i";
  qvl << 84;
  qvl << "f";
  qvl << QVariant::Int;
  i = t1.getRowsByColumnValue(qvl);
  CPPUNIT_ASSERT(i.isValid());
  CPPUNIT_ASSERT(i.length() == 2);
  CPPUNIT_ASSERT(!i.isEnd());

  // test a query that matches zero rows
  qvl.clear();
  qvl << "i";
  qvl << 5000;
  i = t1.getRowsByColumnValue(qvl);
  CPPUNIT_ASSERT(!i.isValid());
  CPPUNIT_ASSERT(i.length() == 0);
  CPPUNIT_ASSERT(i.isEnd());

  printEndMsg();
}

//----------------------------------------------------------------------------

void tstDbTab::testGetAllRows()
{
  printStartMsg("testGetAllRows");

  SampleDB db = getScenario01(dbOverlay::GenericDatabase::SQLITE);
  DbTab t1 = db["t1"];
  
  DbTab::CachingRowIterator i = t1.getAllRows();
  CPPUNIT_ASSERT(i.isValid());
  CPPUNIT_ASSERT(i.length() == 5);
  CPPUNIT_ASSERT(!i.isEnd());
  
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



