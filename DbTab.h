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
    TabRow operator[](const int id) const;
    TabRow operator[](const QVariantList& args ) const;
    TabRow getSingleRowByColumnValue(const QVariantList& args = QVariantList()) const;
    TabRow getSingleRowByColumnValue(const QString& col, const QVariant& val) const;
    TabRow getSingleRowByWhereClause(const QString& where, const QVariantList& args = QVariantList()) const;
    CachingRowIterator getRowsByWhereClause(const QString& where, const QVariantList& args = QVariantList()) const;
    CachingRowIterator getRowsByColumnValue(const QVariantList& args = QVariantList()) const;
    CachingRowIterator getRowsByColumnValue(const QString& col, const QVariant& val) const;
    CachingRowIterator getAllRows() const;
    int deleteRowsByWhereClause(const QString& where, const QVariantList& args = QVariantList()) const;
    int deleteRowsByColumnValue(const QVariantList& args = QVariantList()) const;
    int deleteRowsByColumnValue(const QString& col, const QVariant& val) const;

  private:
    static QHash<QString, DbTab> tabCache;
    DbTab (GenericDatabase* db, const QString& tabName);
  };

}

#endif	/* DBTAB_H */

