/* 
 * File:   DbTab.h
 * Author: volker
 *
 * Created on February 9, 2014, 5:04 PM
 */

#ifndef DBTAB_H
#define	DBTAB_H

#include "CommonTabularClass.h"

#include <QHash>

namespace dbOverlay
{

  class DbTab : public CommonTabularClass
  {
  public:
    static DbTab getTab (GenericDatabase* db, const QString& tabName);
    static void clearTabCache();
    //DbTab (const DbTab& orig);
    virtual ~DbTab ();

  private:
    static QHash<QString, DbTab> tabCache;
    DbTab (GenericDatabase* db, const QString& tabName);
  };

}

#endif	/* DBTAB_H */

