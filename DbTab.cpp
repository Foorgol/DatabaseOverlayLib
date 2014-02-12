/* 
 * File:   DbTab.cpp
 * Author: volker
 * 
 * Created on February 9, 2014, 5:04 PM
 */

#include <qt/QtCore/qjsonarray.h>

#include "DbTab.h"
#include "HelperFunc.h"
#include "dbExceptions.h"

namespace dbOverlay
{
  QHash<QString, DbTab> DbTab::tabCache;

//----------------------------------------------------------------------------

  DbTab DbTab::getTab(GenericDatabase* _db, const QString& _tabName)
  {
    QHash<QString, DbTab>::const_iterator i = tabCache.find(_tabName);
    while (i != tabCache.end())
    {
      if ((*i).db == _db)
      {
        return (*i);
      }
      
      i++;
    }
    
    DbTab newTab(_db, _tabName);
    tabCache.insert(_tabName, newTab);
    
    return newTab;
  }

//----------------------------------------------------------------------------

  DbTab::~DbTab()
  {
  }

//----------------------------------------------------------------------------

  DbTab GenericDatabase::getTab(const QString& name)
  {
    return DbTab::getTab(this, name);
  }
  
  DbTab GenericDatabase::operator [](const QString& name)
  {
    return DbTab::getTab(this, name);
  }
  
//----------------------------------------------------------------------------

  DbTab::DbTab(GenericDatabase* _db, const QString& _tabName)
  : CommonTabularClass (_db, _tabName, false)
  {

  }

//----------------------------------------------------------------------------

  void DbTab::clearTabCache()
  {
    tabCache.clear();
  }

//----------------------------------------------------------------------------

  int DbTab::insertRow(const QVariantList& args)
  {
    if ((args.length() % 2) != 0)
    {
      throw std::invalid_argument("Insert row: Need an even number of arguments (column / value pairs)");
    }
    
    // split the combined column/values list in "args" into two separate lists
    QStringList colNames;
    QStringList placeholders;
    QVariantList vals;
    QVariantList::const_iterator i = args.begin();
    while (i != args.end())
    {
      colNames << (*i).toString();
      i++;
      vals << (*i);
      i++;
      placeholders << "?";
    }
    
    // create the SQL statement
    QString sql;
    if (args.length() > 0)
    {
      sql = "INSERT INTO " + tabName + " (";
      sql += commaSepStringFromList(colNames);
      sql += ") VALUES (";
      sql += commaSepStringFromList(placeholders);
      sql += ")";
    } else
    {
      // special case: insert default values only
      if (db->getDbType() == GenericDatabase::SQLITE)
      {
        sql = "INSERT INTO " + tabName + " DEFAULT VALUES";
      } else {
        sql = "INSERT INTO " + tabName + " () VALUES ()";
      }
      vals.clear();  // shouldn't be necessary...
    }
    
    // execute the insert
    int result = db->execNonQuery(sql, vals);
    if (result != 1)
    {
      //throw WriteDataFailedException(QString2String(tabName));
      return -1;
    }
    
    // get the ID of the last insert
    return db->getLastInsertId();
  }

//----------------------------------------------------------------------------

  int DbTab::insertRow()
  {
    QVariantList emptyList;
    return insertRow(emptyList);
  }

//----------------------------------------------------------------------------

  TabRow DbTab::operator [](const int id)
  {
    return TabRow(db, tabName, id);
  }

//----------------------------------------------------------------------------

  TabRow DbTab::operator [](const QVariantList& args)
  {
    return TabRow(db, tabName, args);
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

}