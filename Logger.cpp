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

#include "Logger.h"
#include "dbExceptions.h"

namespace dbOverlay
{

    Logger::Logger(QString senderName)  : sender(senderName), threshold(LVL_INFO), defaultLevel(LVL_CRITICAL) {
        info("####### '" + sender + "' starts logging #####");
    }

    Logger::~Logger()
    {
        info("####### '" + sender + "' stops logging #####");
    }
    
    Logger::Logger()
    {
      sender = "<<invalid>>";
    }
    
    void Logger::warn (const QString msg)
    {
        log(LVL_WARN, msg);
    }
    
    void Logger::critical (const QString msg)
    {
        log(LVL_CRITICAL, msg);
    }
    
    void Logger::info (const QString msg)
    {
        log(LVL_INFO, msg);
    }
    
    void Logger::log(const int logLvl, const QString msg)
    {
        if (logLvl < threshold) return;
        
        QString txt;
        if (logLvl == LVL_CRITICAL) txt = "CRITICAL";
        else if (logLvl == LVL_WARN) txt = "Warning";
        else txt = "Info";
        
        txt +=" - " + sender + ": " + msg;
        
        qDebug() << txt;
    }
    
    void Logger::log(const QString msg)
    {
        log(defaultLevel, msg);
    }
    
    void Logger::setDefaultLevel(const int newDefaultLvl)
    {
        if (!(isValidLevel(newDefaultLvl)))
        {
            throw InvalidLogLevelException(newDefaultLvl);
        }
        
        defaultLevel = newDefaultLvl;
    }
    
    void Logger::setLevel(const int newLvl)
    {
        if (!(isValidLevel(newLvl)))
        {
            throw InvalidLogLevelException(newLvl);
        }
        
        threshold = newLvl;
    }
    
    bool Logger::isValidLevel(const int lvl) {
        return ((lvl >= LVL_WARN) && (lvl <= LVL_CRITICAL));
    }


}
