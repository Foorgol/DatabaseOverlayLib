/* 
 * File:   tstGenericDatabase.cpp
 * Author: volker
 * 
 * Created on February 2, 2014, 1:02 PM
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


//----------------------------------------------------------------------------


//----------------------------------------------------------------------------



