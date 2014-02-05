/* 
 * File:   BasicTestClass.h
 * Author: volker
 *
 * Created on February 1, 2014, 9:31 PM
 */

#ifndef BASICTESTCLASS_H
#define	BASICTESTCLASS_H

#include <string>

#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include <QtCore>
#include <QTemporaryFile>
#include <QTemporaryDir>

#include "Logger.h"

class BasicTestClass : public QObject, public CppUnit::TestFixture
{
  Q_OBJECT

public:
  virtual void setUp ();
  virtual void tearDown ();

protected:
  QString getTestDir ();
  QString genTestFilePath(QString fName);
  QTemporaryDir tstDir;
  dbOverlay::Logger *log;
  void printStartMsg(QString);
  void printEndMsg();

private:
  QString tcName;
};

#endif	/* BASICTESTCLASS_H */

