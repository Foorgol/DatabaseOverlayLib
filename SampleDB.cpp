/*
 *    This is DatabaseOverlayLib, a database abstraction layer on top of Qt.
 *    Copyright (C) 2014 - 2015  Volker Knollmann
 *
 *    This program is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with this program.  If not, see <http://www.gnu.org/licenses/>.
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
