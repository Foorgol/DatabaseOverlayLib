/* 
 * File:   BasicTestClass.cpp
 * Author: volker
 * 
 * Created on February 1, 2014, 9:31 PM
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
    log = new dbOverlay::Logger("UnitTest");
    
    // create a dir for temporary files created during testing
    if (!(tstDir.isValid()))
    {
        throw std::runtime_error("Could not create temporary directory for test files!");
    }
    
    log->info("Created directory " + tstDir.path() + " for temporary files");
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
    
    log->info("Deleted temporary directory " + tstDir.path() + " and all its contents");
    
    delete log;
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