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

#ifndef DBTAB_H
#define	DBTAB_H

#include "CommonTabularClass.h"
#include "TabRow.h"

#include <QHash>

namespace dbOverlay
{

  class DbTab : public CommonTabularClass
  {
  public:
    class CachingRowIterator
    {
    public:
      CachingRowIterator(GenericDatabase* db, const QString& tabName, QSqlQuery& qry);
      void operator++();
      TabRow operator*() const;
      bool isEnd() const;
      bool isValid() const;
      int length() const;
      
    private:
      QList<int> idList;
      GenericDatabase* db;
      QString tabName;
      QList<int>::const_iterator listIter;
    };
    
  public:
    static DbTab getTab (GenericDatabase* db, const QString& tabName);
    static void clearTabCache();
    //DbTab (const DbTab& orig);
    virtual ~DbTab ();
    int insertRow(const QVariantList& args);
    int insertRow();
    TabRow operator[](const int id);
    TabRow operator[](const QVariantList& args );
    TabRow getSingleRowByColumnValue(const QVariantList& args = QVariantList()) const;
    TabRow getSingleRowByColumnValue(const QString& col, const QVariant& val) const;
    TabRow getSingleRowByWhereClause(const QString& where, const QVariantList& args = QVariantList()) const;
    CachingRowIterator getRowsByWhereClause(const QString& where, const QVariantList& args = QVariantList()) const;
    CachingRowIterator getRowsByColumnValue(const QVariantList& args = QVariantList()) const;
    CachingRowIterator getAllRows() const;

  private:
    static QHash<QString, DbTab> tabCache;
    DbTab (GenericDatabase* db, const QString& tabName);
  };

}

#endif	/* DBTAB_H */

