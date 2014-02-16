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

class BasicTestClass : public CppUnit::TestFixture
{

public:
  virtual void setUp ();
  virtual void tearDown ();

protected:
  QString getTestDir ();
  QString genTestFilePath(QString fName);
  QTemporaryDir tstDir;
  dbOverlay::Logger log;
  void printStartMsg(QString);
  void printEndMsg();

private:
  QString tcName;
};

#endif	/* BASICTESTCLASS_H */

