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
    int getId();
    bool update(const QVariantList& args);
    bool update(const QString& colName, const QVariant& newVal);
    QVariant operator[](const QString& colName);
    inline bool operator== (const TabRow& other) const
    {
      return ((other.tabName == tabName) && (other.rowId == rowId));   // do not check database handle here to allow comparision between different instances that share the same db
    }
    inline bool operator!= (const TabRow& other) const
    {
      return (!(this->operator == (other)));
    }
    GenericDatabase getDb();
    
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

