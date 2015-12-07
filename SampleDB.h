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

#ifndef SAMPLEDB_H
#define	SAMPLEDB_H

#include "GenericDatabase.h"

using namespace dbOverlay;

class SampleDB : public GenericDatabase
{
public:
  virtual void populateTables();
  virtual void populateViews();
  
  SampleDB(DB_ENGINE t, QString srv, int port, QString name, QString user, QString pw) :
  GenericDatabase(t, srv, port, name, user, pw) {};
  SampleDB() : GenericDatabase() {};
  SampleDB(QString sqliteFilename, bool createNew) : GenericDatabase(sqliteFilename, createNew) {};
  
private:
};

#endif	/* SAMPLEDB_H */

