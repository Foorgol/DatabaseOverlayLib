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
  TabRow::TabRow(GenericDatabase* _db, const QString& _tabName, int _rowId, bool skipCheck)
  : db(_db), tabName(_tabName), rowId(_rowId)
  {
    // Dangerous short-cut for lib-internal purposes:
    // if we're told that _db, _tabName and _rowId are GUARANTEED to be correct
    // (e. g. they result from a previous SELECT), we don't need further database
    // queries to check them again
    if (skipCheck)
    {
      return; // all done
    }
    
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

  int TabRow::getId() const
  {
    return rowId;
  }

//----------------------------------------------------------------------------

  bool TabRow::update(const QVariantList& args) const
  {
    if (args.length() == 0)
    {
      return true;  // nothing to do
    }
    
    if ((args.length() % 2) != 0)
    {
      throw std::invalid_argument("Update row: Need an even number of arguments (column / value pairs)");
    }
    
    // create the SQL statement
    QString sql = "UPDATE " + tabName + " SET ";
    
    // split the combined column/values list in "args" into a separate list of values
    QVariantList vals;
    QVariantList::const_iterator i = args.begin();
    while (i != args.end())
    {
      QString colName = (*i).toString();
      if (colName == "id")
      {
        throw std::invalid_argument("Update row: can't alter value of the ID column!");
      }
      sql += colName + " = ?, ";
      i++;
      vals << (*i);
      i++;
    }
    
    // remove the trailing ", "
    sql = sql.left(sql.length() - 2);
    
    // complete the statement
    sql += " WHERE id = ?";
    vals << rowId;
    
    int result = db->execNonQuery(sql, vals);
    
    return (result == 1);
  }

//----------------------------------------------------------------------------

  QVariant TabRow::operator [](const QString& colName) const
  {
    if ((colName == NULL) || (colName.length() == 0))
    {
      throw std::invalid_argument("Column access: received empty column name");
    }
    
    QString sql = "SELECT " + colName + " FROM " + tabName + " WHERE id = " + QString::number(rowId);
    
    QVariant result = db->execScalarQuery(sql);
    if (!(result.isValid()))
    {
      throw std::invalid_argument("Column access: received invalid column name or row has been deleted in the meantime");
    }
    
    return result;
  }


//----------------------------------------------------------------------------

  bool TabRow::update(const QString& colName, const QVariant& newVal) const
  {
    QVariantList qvl;
    qvl << colName << newVal;
    return update(qvl);
  }

//----------------------------------------------------------------------------

  GenericDatabase* TabRow::getDb()
  {
    return db;
  }

//----------------------------------------------------------------------------

  bool TabRow::erase()
  {
    QString sql = "DELETE FROM " + tabName + " WHERE id = " + QString::number(rowId);
    bool success = (db->execNonQuery(sql) != 0);
    
    // make this instance unusable by setting the ID to an invalid value
    if (success)
    {
      rowId = -1;
    }
    
    return success;
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

}
