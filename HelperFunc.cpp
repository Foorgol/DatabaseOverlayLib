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

#include "HelperFunc.h"

#include <QtCore>
#include <QStringList>
#include <QVariantList>
#include <qt/QtCore/qjsonarray.h>
#include <stdexcept>

namespace dbOverlay
{
  const string QString2String(const QString &inString)
  {
    QByteArray ba = inString.toUtf8 ();
    return ba.constData ();
  }

//----------------------------------------------------------------------------
    
  QString commaSepStringFromList(const QVariantList& lst)
  {
    QString result;
    bool hasElements = false;
    
    for (int i=0; i<lst.size(); i++)
    {
      QVariant v = lst.at(i);
      
      if (v.isNull())
      {
        qDebug() << "commaSepStringFromList: skipped null-element at index " + QString::number(i);
        continue;
      }
      
      if (!v.canConvert<QString>())
      {
        qDebug() << "commaSepStringFromList: can't convert element at index " + QString::number(i) + " to QString";
        result += "<Not convertable to QString>";
      } else {
        if (hasElements)
        {
          result += ", ";
        }
        result += v.toString();
      }
      
      hasElements = true;
    }
    
    return result;
  }

//----------------------------------------------------------------------------
    
  QString commaSepStringFromList(const QStringList& lst)
  {
    QVariantList qvl;
    for (int i=0; i<lst.size(); i++)
    {
      qvl << lst.at(i);
    }
    
    return commaSepStringFromList(qvl);
  }

//----------------------------------------------------------------------------

  /**
   * Takes columnname / value pairs and constructs a WHERE clause using
   * placeholders ("?") and proper handling of NULL.
   * 
   * @param args a list of column / value pairs
   * 
   * @return a QVariantList with the WHERE-clause at index 0 and the parameters for the placeholders at index 1+
   */
  QVariantList prepWhereClause(const QVariantList& args)
  {
    QString whereClause = "";

    // check for an EVEN number of arguments
    if ((args.length() % 2) != 0)
    {
      throw std::invalid_argument("Need an even number of arguments (column / value pairs)");
    }

    // for the return value, create a list of the parameter objects
    // plus the WHERE-clause at index 0
    QVariantList result;

    for (int i=0; i < args.length(); i += 2)
    {
      whereClause += args[i].toString();
      if (args[i+1].isNull()) whereClause += " IS NULL";
      else
      {
        whereClause += " = ?";
        result.append(args[i+1]);
      }
      if (i != (args.length() - 2)) whereClause += " AND ";
    }

    result.insert(0, whereClause);

    return result;
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
    
}
