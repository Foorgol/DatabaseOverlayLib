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

  class CommonTabularClass
  {
  public:
    CommonTabularClass (GenericDatabase* db, const QString& tabName, bool _isView=false );
    CommonTabularClass (const CommonTabularClass& orig);
    virtual ~CommonTabularClass ();

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

