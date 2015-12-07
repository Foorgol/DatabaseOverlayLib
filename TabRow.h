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

#ifndef TABROW_H
#define	TABROW_H

#include "GenericDatabase.h"
#include "CommonTabularClass.h"

namespace dbOverlay
{

  /**
   * A class representing a single data row in a table (not in a view!)
   * 
   * @author volker
   */
  class TabRow
  {
  public:
    TabRow (GenericDatabase* db, const QString& _tabName, int _rowId, bool skipCheck = false);
    TabRow (GenericDatabase* db, const QString& _tabName, const QVariantList& params);
    //TabRow (const TabRow& orig);
    virtual ~TabRow ();
    int getId() const;
    bool update(const QVariantList& args) const;
    bool update(const QString& colName, const QVariant& newVal) const;
    QVariant operator[](const QString& colName) const;
    inline bool operator== (const TabRow& other) const
    {
      return ((other.tabName == tabName) && (other.rowId == rowId));   // do not check database handle here to allow comparision between different instances that share the same db
    }
    inline bool operator!= (const TabRow& other) const
    {
      return (!(this->operator == (other)));
    }
    GenericDatabase* getDb();
    bool erase();
    
  protected:
    /**
     * the handle to the (parent) database
     */
    GenericDatabase* db;
    
    /**
     * the name of the associated table
     */
    QString tabName;
    
    /**
     * the unique index of the data row
     */
    int rowId;
    
    bool doInit(const QString& whereClause, const QVariantList& params);

  private:

  };
}

#endif	/* TABROW_H */

