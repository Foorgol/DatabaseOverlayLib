/* 
 * File:   TabRow.cpp
 * Author: volker
 * 
 * Created on February 9, 2014, 4:27 PM
 */

#include <qt/QtCore/qjsonarray.h>

#include "TabRow.h"
#include "dbExceptions.h"
#include "HelperFunc.h"
#include "DbTab.h"

namespace dbOverlay
{

  /**
   * Constructor for a known rowID
   * 
   * @param _db the associated database instance
   * @param _tabName the associated table name
   * @param _rowId 
   */
  TabRow::TabRow(GenericDatabase* _db, const QString& _tabName, int _rowId)
  : db(_db), tabName(_tabName), rowId(_rowId)
  {
    QVariantList emptyList;
    doInit("id = " + QString::number(rowId), emptyList);
  }

//----------------------------------------------------------------------------

  /**
   * Constructor for the first row in the table that matches a column/value pair or a custom where clause.
   * 
   * If the first elements of "args" is a column name, then args is interpreted
   * as a set of column/value pairs which shall be AND-concatenated.
   * 
   * If the first element of "args" is NOT a column name, then the first element
   * is interpreted as a where clause and all subsequent elements are treated as
   * parameters ("?") to that where clause
   * 
   * Throws an exception if the requested row doesn't exist
   * 
   * @param _db the associated database instance
   * @param _tabName the associated table name
   * @param args where clause and/or column/value pairs
   */
  TabRow::TabRow(GenericDatabase* _db, const QString& _tabName, const QVariantList& params)
  : db(_db), tabName(_tabName), rowId(-1)
  {
    doInit("", params);
  }

//----------------------------------------------------------------------------

//  TabRow::TabRow(const TabRow& orig)
//  {
//  }

//----------------------------------------------------------------------------

  TabRow::~TabRow()
  {
  }

//----------------------------------------------------------------------------

  bool TabRow::doInit(const QString& whereClause, const QVariantList& params)
  {
    // make sure the database handle is correct
    if (db == NULL)
    {
      throw EmptyDatabaseHandleException();
    }
    
    // make sure the table name exists
    // the check is performed by the DbTab constructor (so we don't
    // need to re-write it here) and we can reuse the DbTab instance later
    // in this method
    DbTab tab = db->getTab(tabName);
    
    // Case 1: we already have a where clause for identifying the row
    if (whereClause.length() > 0)
    {
      QVariant result = db->execScalarQuery("SELECT id FROM " + tabName + " WHERE " + whereClause, params);
      if (result.isNull())
      {
        throw InvalidRowQualifierException();
      }
      rowId = result.toInt();
      
      return true;
    }
    
    // if we made it this far, we need to construct the where clause from either
    //    - the first argument in the params list; or
    //    - a standard where clause that ANDs all column/value pairs in the params list
    //
    
    // whatever case: we need a non-empty params list
    if (params.isEmpty())
    {
      throw InvalidRowQualifierException();
    }
    
    QString firstPara = params.at(0).toString();
    
    // Case 2:
    // all params are column/value pairs that should be ANDed
    //
    // We generate the where clause and transform this case into
    // "Case 3" (see below)
    QVariantList convertedParams;
    if (tab.hasColumn(firstPara))
    {
      convertedParams = prepWhereClause(params);
    } else {
      convertedParams = params;
    }

    // Case 3:
    // where clause in the first parameter entry and
    // all subsequent entries are placeholder-values
    // for the where-clause
    QString where = convertedParams.at(0).toString();
    QVariantList placeholders;
    if (convertedParams.length() > 1)
    {
      placeholders = convertedParams.mid(1);
    }

    QVariant result = db->execScalarQuery("SELECT id FROM " + tabName + " WHERE " + where, placeholders);
    if (result.isNull())
    {
      throw InvalidRowQualifierException();
    }
    rowId = result.toInt();

    return true;
  }

//----------------------------------------------------------------------------

  int TabRow::getId()
  {
    return rowId;
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


//----------------------------------------------------------------------------


//----------------------------------------------------------------------------


//----------------------------------------------------------------------------


//----------------------------------------------------------------------------


//----------------------------------------------------------------------------


//----------------------------------------------------------------------------


//----------------------------------------------------------------------------


//----------------------------------------------------------------------------

}