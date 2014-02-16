/* 
 * File:   CommonTabularClass.h
 * Author: volker
 *
 * Created on February 8, 2014, 7:12 PM
 */

#ifndef COMMONTABULARCLASS_H
#define	COMMONTABULARCLASS_H

#include "GenericDatabase.h"

namespace dbOverlay
{

    /**
   * A small struct with schema information about a column
   *
   * @author volker
   */
  class ColInfo
  {
  public:

    ColInfo (int _cid, QString _name, QString _type)
    : cid (_cid), name (_name), type (_type.toUpper ()) { };

    int getId () const;
    QString getColName () const;
    QString getColType () const;
    
  protected:
    int cid;
    QString name;
    QString type;
    
  };
  
  typedef QList<ColInfo> ColInfoList;
  

  class CommonTabularClass
  {
  public:
    CommonTabularClass (GenericDatabase* db, const QString& tabName, bool _isView=false );
    //CommonTabularClass (const CommonTabularClass& orig) {};
    virtual ~CommonTabularClass ();
    
    ColInfoList allColDefs() const;
    QString getColType(const QString& colName) const;
    QString cid2name(int cid) const;
    int name2cid(const QString& colName) const;
    bool hasColumn(const QString& colName) const;
    bool hasColumn(int cid) const;
    int getMatchCountForWhereClause(const QString& where, const QVariantList& args) const;
    int getMatchCountForWhereClause(const QString& where) const;
    int getMatchCountForColumnValue(const QVariantList& args) const;
    int length() const;

  protected:
    /**
     * the handle to the (parent) database
     */
    GenericDatabase* db;
    
    /**
     * the name of the associated table or view
     */
    QString tabName;
    
    /**
     * a tag whether we are a view or a tab
     */
    bool isView;

  private:

  };

}
#endif	/* COMMONTABULARCLASS_H */

