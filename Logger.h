/* 
 * File:   Logger.h
 * Author: volker
 *
 * Created on February 1, 2014, 8:45 PM
 */

#ifndef LOGGER_H
#define	LOGGER_H

#include <QString>
#include <QtCore>

namespace dbOverlay
{

  class Logger
  {
  public:
    Logger (QString senderName);
    Logger ();
    virtual ~Logger ();

    void warn (const QString msg);
    void critical (const QString msg);
    void info (const QString msg);
    void log(const int logLvl, const QString msg);
    void log(const QString msg);
    void setDefaultLevel(const int newDefaultLvl);
    void setLevel(const int newLvl);
    
    static const int LVL_CRITICAL = 2;
    static const int LVL_WARN = 1;
    static const int LVL_INFO = 0;
    
  private:

    QString sender;
    int threshold;
    int defaultLevel;
    
    bool isValidLevel(const int lvl);
    
  };
}

#endif	/* LOGGER_H */

