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

#include <QString>
#include "KeyValueTab.h"
#include "HelperFunc.h"

namespace dbOverlay
{
  const QString KeyValueTab::KEY_COL_NAME = QString("K");
  const QString KeyValueTab::VAL_COL_NAME = QString("V");
  const int KeyValueTab::MAX_KEY_LEN = 100;
    
//----------------------------------------------------------------------------
    
  KeyValueTab::KeyValueTab(GenericDatabase* _db, const QString& _tabName)
  : db(_db), tabName(_tabName), tab((*_db)[tabName])
  {
    // make sure that the table has the columns for keys and values
    if (!(tab.hasColumn(KEY_COL_NAME)))
    {
      throw std::invalid_argument("KeyValueTab ctor: table " + QString2String(tabName) + " has no valid key column");
    }
    if (!(tab.hasColumn(VAL_COL_NAME)))
    {
      throw std::invalid_argument("KeyValueTab ctor: table " + QString2String(tabName) + " has no valid value column");
    }
  }
    
//----------------------------------------------------------------------------

  KeyValueTab KeyValueTab::getTab(GenericDatabase* _db, const QString& _tabName)
  {
    if (_db == NULL)
    {
      throw std::invalid_argument("KeyValueTab::get: got NULL handle for database");
    }
    
    // check if the table exists. If not, create it
    if (!(_db->hasTable(_tabName)))
    {
      QStringList colDefs;
      colDefs << KEY_COL_NAME + " VARCHAR(" + QString::number(MAX_KEY_LEN) + ")";
      colDefs << VAL_COL_NAME + " TEXT";
      _db->tableCreationHelper(_tabName, colDefs);
    }
    
    return KeyValueTab(_db, _tabName);
  }
    
//----------------------------------------------------------------------------

  void KeyValueTab::set(const QString& key, const QVariant& val)
  {
    QVariantList args;
    
    if (hasKey(key))
    {
      QString sql = "UPDATE " + tabName + " SET " + VAL_COL_NAME + " = ? ";
      sql += "WHERE " + KEY_COL_NAME + " = ?";
      
      args << val << key;
      db->execNonQuery(sql, args);
    } else {
      args << KEY_COL_NAME << key;
      args << VAL_COL_NAME << val;
      tab.insertRow(args);
    }
  }
    
//----------------------------------------------------------------------------
    
  QVariant KeyValueTab::operator [](const QString& key) const
  {
    QString sql = "SELECT " + VAL_COL_NAME + " FROM " + tabName + " WHERE ";
    sql += KEY_COL_NAME + " = ?";
    
    QVariantList args;
    args << key;
    
    return db->execScalarQuery(sql, args);
  }
    
//----------------------------------------------------------------------------
    
  bool KeyValueTab::hasKey(const QString& key) const
  {
    QVariantList args;
    args << KEY_COL_NAME;
    args << key;
    
    return (tab.getMatchCountForColumnValue(args) > 0);
  }
    
//----------------------------------------------------------------------------
    
  int KeyValueTab::getInt(const QString& key) const
  {
    QVariant val = (*this)[key];
    return val.toInt();
  }
    
//----------------------------------------------------------------------------

  bool KeyValueTab::getBool(const QString& key) const
  {
    QVariant val = (*this)[key];
    return val.toBool();
  }
    
//----------------------------------------------------------------------------

  QString KeyValueTab::getString(const QString& key) const
  {
    QVariant val = (*this)[key];
    return val.toString();
  }
    
//----------------------------------------------------------------------------

  double KeyValueTab::getDouble(const QString& key) const
  {
    QVariant val = (*this)[key];
    return val.toDouble();
  }
    
//----------------------------------------------------------------------------
    
    
//----------------------------------------------------------------------------
    
    
//----------------------------------------------------------------------------
    
    
//----------------------------------------------------------------------------
    
    
//----------------------------------------------------------------------------
    
    
//----------------------------------------------------------------------------
    
    
//----------------------------------------------------------------------------
    
    
//----------------------------------------------------------------------------
    
    
//----------------------------------------------------------------------------
    
    
//----------------------------------------------------------------------------
    
    
//----------------------------------------------------------------------------
    
    
//----------------------------------------------------------------------------
    
    
//----------------------------------------------------------------------------
    
    
//----------------------------------------------------------------------------
    
    
//----------------------------------------------------------------------------
    
    
//----------------------------------------------------------------------------
    
    
//----------------------------------------------------------------------------
    
    
//----------------------------------------------------------------------------
    
}
