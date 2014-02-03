/* 
 * File:   SampleDB.h
 * Author: volker
 *
 * Created on February 2, 2014, 12:59 PM
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

