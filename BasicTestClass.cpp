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

#include <qt/QtCore/qtemporarydir.h>

#include "BasicTestClass.h"
#include "../qt4/QtCore/qbytearray.h"
#include <stdexcept>
#include <qt/QtCore/qstring.h>

#include "Logger.h"
#include "../qt4/QtCore/qstring.h"

void BasicTestClass::setUp()
{
  qDebug() << "\n\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n\n";

  log = dbOverlay::Logger("UnitTest");

  // create a dir for temporary files created during testing
  if (!(tstDir.isValid()))
  {
    throw std::runtime_error("Could not create temporary directory for test files!");
  }

  log.info("Created directory " + tstDir.path() + " for temporary files");
}

void BasicTestClass::tearDown()
{
  QString path = tstDir.path();

  if (!(tstDir.remove()))
  {
    QString msg = "Could not remove temporary directory " + path;
    QByteArray ba = msg.toLocal8Bit();
    throw std::runtime_error(ba.data());
  }

  log.info("Deleted temporary directory " + tstDir.path() + " and all its contents");
}

QString BasicTestClass::getTestDir()
{
  return tstDir.path();
}

QString BasicTestClass::genTestFilePath(QString fName)
{
  QString finalPath = tstDir.path();
  finalPath += QDir::separator() + fName;

  return QDir::cleanPath(finalPath);
}

void BasicTestClass::printStartMsg(QString _tcName)
{
  tcName = _tcName;
  log.info("\n\n----------- Starting test case '" + tcName + "' -----------");
}

void BasicTestClass::printEndMsg()
{
  log.info("----------- End test case '" + tcName + "' -----------\n\n");
}