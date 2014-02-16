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

