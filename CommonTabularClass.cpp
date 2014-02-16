/* 
 * File:   CommonTabularClass.cpp
 * Author: volker
 * 
 * Created on February 8, 2014, 7:12 PM
 */

#include <qt/QtCore/qjsonarray.h>

#include "CommonTabularClass.h"
#include "dbExceptions.h"
#include "HelperFunc.h"

namespace dbOverlay
{

  int ColInfo::getId() const
  {
    return cid;
  }
  
//----------------------------------------------------------------------------

  QString ColInfo::getColName() const
  {
    return name;
  }

//----------------------------------------------------------------------------

  QString ColInfo::getColType() const
  {
    return type;
  }

//----------------------------------------------------------------------------

  /**
   * Basic constructor of a table or view
   * 
   * @param _db the reference to the database instance for this table / view
   * @param _tabName the name of the table / view
   * @param _isView true if name refers to a view and "false" for tables
   */
  CommonTabularClass::CommonTabularClass(GenericDatabase* _db, const QString& _tabName, bool _isView)
  : db(_db), tabName(_tabName), isView(_isView)
  {
    if (db == NULL)
    {
      throw EmptyDatabaseHandleException();
    }
    
    if (_tabName.length() == 0)
    {
      throw InvalidTabNameException();
    }
    
    if ((isView) && (!db->hasView(tabName)))
    {
      throw InvalidTabNameException(QString2String(tabName));
    }
    
    if ((!isView) && (!db->hasTable(tabName)))
    {
      throw InvalidTabNameException(QString2String(tabName));
    }
  }

//----------------------------------------------------------------------------

  CommonTabularClass::~CommonTabularClass()
  {
  }

//----------------------------------------------------------------------------

  ColInfoList CommonTabularClass::allColDefs() const
  {
    ColInfoList result;
    QSqlQuery* qry;
    
    if (db->getDbType() == GenericDatabase::SQLITE)
    {
      qry = db->execContentQuery("PRAGMA table_info(" + tabName + ")");
      
      while (qry->next())
      {
        ColInfo ci(qry->value(0).toInt(), qry->value(1).toString(), qry->value(2).toString());
        result << ci;
      }
      
    } else {
      
      qry = db->execContentQuery("DESCRIBE " + tabName);
      
      int i=0;
      while (qry->next())
      {
        ColInfo ci(i, qry->value(0).toString(), qry->value(1).toString());
        result << ci;
        i++;
      }
      
    }
    
    delete qry;
    
    return result;
  }

//----------------------------------------------------------------------------

  QString CommonTabularClass::getColType(const QString& colName) const
  {
    ColInfoList cil = allColDefs();
    ColInfoList::const_iterator i;
    
    for (i = cil.constBegin(); i != cil.constEnd(); ++i)
    {
      if ((*i).getColName() == colName)
      {
        return (*i).getColType();
      }
    }
    
    return QString();
  }

//----------------------------------------------------------------------------

  QString CommonTabularClass::cid2name(int cid) const
  {
    ColInfoList cil = allColDefs();
    ColInfoList::const_iterator i;
    
    for (i = cil.constBegin(); i != cil.constEnd(); ++i)
    {
      if ((*i).getId() == cid)
      {
        return (*i).getColName();
      }
    }
    
    return QString();
  }

//----------------------------------------------------------------------------

  int CommonTabularClass::name2cid(const QString& colName) const
  {
    ColInfoList cil = allColDefs();
    ColInfoList::const_iterator i;
    
    for (i = cil.constBegin(); i != cil.constEnd(); ++i)
    {
      if ((*i).getColName() == colName)
      {
        return (*i).getId();
      }
    }
    
    return -1;
  }

//----------------------------------------------------------------------------

  bool CommonTabularClass::hasColumn(const QString& colName) const
  {
    ColInfoList cil = allColDefs();
    ColInfoList::const_iterator i;
    
    for (i = cil.constBegin(); i != cil.constEnd(); ++i)
    {
      if ((*i).getColName() == colName)
      {
        return true;
      }
    }
    
    return false;
  }

//----------------------------------------------------------------------------

  bool CommonTabularClass::hasColumn(int cid) const
  {
    ColInfoList cil = allColDefs();
    
    return ((cid >= 0) && (cid < cil.length()));
  }

//----------------------------------------------------------------------------

  int CommonTabularClass::getMatchCountForWhereClause(const QString& where, const QVariantList& args) const
  {
    QString sql = "SELECT count(*) FROM " + tabName + " WHERE " + where;
    QVariant result = db->execScalarQuery(sql, args);

    if (result.isNull())
    {
      return -1; // error in the query
    }

    bool ok;
    int cnt = result.toInt(&ok);

    if (!ok)
    {
      return 0;  // successful query, but non-int result. Shouldn't happen
    }

    return cnt;
  }


//----------------------------------------------------------------------------

  int CommonTabularClass::getMatchCountForWhereClause(const QString& where) const
  {
    QVariantList empty;
    return getMatchCountForWhereClause(where, empty);
  }


//----------------------------------------------------------------------------

  int CommonTabularClass::getMatchCountForColumnValue(const QVariantList& args) const
  {
    QVariantList qvl;
    
    try
    {
      qvl = prepWhereClause(args);
    }
    catch (std::invalid_argument e)
    {
      return -1;
    }
    
    QString sql = "SELECT count(*) FROM " + tabName + " WHERE " + qvl.at(0).toString();
    QVariant result;
    if (qvl.length() > 1)
    {
      qvl.removeFirst();
      result = db->execScalarQuery(sql, qvl);
    } else {
      result = db->execScalarQuery(sql);
    }
    
    if (result.isNull())
    {
      return -1; // error in the query
    }

    bool ok;
    int cnt = result.toInt(&ok);

    if (!ok)
    {
      return 0;  // successful query, but non-int result. Shouldn't happen
    }

    return cnt;
  }

//----------------------------------------------------------------------------

  int CommonTabularClass::length() const
  {
    QString sql = "SELECT count(*) FROM " + tabName;
    return (db->execScalarQuery(sql)).toInt();
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