/* 
 * File:   TabRow.h
 * Author: volker
 *
 * Created on February 9, 2014, 4:27 PM
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
    TabRow (GenericDatabase* db, const QString& _tabName, int _rowId);
    TabRow (GenericDatabase* db, const QString& _tabName, const QVariantList& params);
    //TabRow (const TabRow& orig);
    virtual ~TabRow ();
    int getId();
    bool update(const QVariantList& args);
    
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

