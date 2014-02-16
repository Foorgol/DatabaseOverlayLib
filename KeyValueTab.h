/* 
 * File:   KeyValueTab.h
 * Author: volker
 *
 * Created on February 15, 2014, 8:50 PM
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

