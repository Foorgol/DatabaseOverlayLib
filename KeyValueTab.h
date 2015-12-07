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

#ifndef KEYVALUETAB_H
#define	KEYVALUETAB_H

#include "GenericDatabase.h"
#include "DbTab.h"

namespace dbOverlay
{

  class KeyValueTab
  {
  public:
    static KeyValueTab getTab(GenericDatabase* _db, const QString& _tabName);
    void set(const QString& key, const QVariant& val);
    QVariant operator[](const QString& key) const;
    bool hasKey(const QString& key) const;
    int getInt(const QString& key) const;
    bool getBool(const QString& key) const;
    QString getString(const QString& key) const;
    double getDouble(const QString& key) const;

  private:
    KeyValueTab (GenericDatabase* _db, const QString& _tabName);
    GenericDatabase* db;
    QString tabName;
    DbTab tab;

    static const QString KEY_COL_NAME;
    static const QString VAL_COL_NAME;
    static const int MAX_KEY_LEN;
  };
  
}
#endif	/* KEYVALUETAB_H */

