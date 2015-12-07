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

