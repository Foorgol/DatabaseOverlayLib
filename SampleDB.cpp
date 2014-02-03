/* 
 * File:   SampleDB.cpp
 * Author: volker
 * 
 * Created on February 2, 2014, 12:59 PM
 */

#include "SampleDB.h"
#include <QString>
#include <QList>

void SampleDB::populateTables()
{
  QList<QString> col;
  col << "i INTEGER" << "f DOUBLE" << "s VARCHAR(40)" << "d DATETIME";
  tableCreationHelper("t1", col);
  tableCreationHelper("t2", col);
}

void SampleDB::populateViews()
{
  viewCreationHelper("v1", "SELECT i,f,s FROM t1 WHERE i=84");
}
