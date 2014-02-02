/* 
 * File:   Logger.cpp
 * Author: volker
 * 
 * Created on February 1, 2014, 8:45 PM
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