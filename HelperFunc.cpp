/* 
 * File:   HelperFunc.cpp
 * Author: volker
 * 
 * Created on February 2, 2014, 10:31 AM
 */

#include "HelperFunc.h"

#include <QtCore>

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
        result += v.toString();
      }
      
      if (i != (lst.size()-1))
      {
        result += ", ";
      }
    }
    
    return result;
  }

//----------------------------------------------------------------------------
    
  QString commaSepStringFromList(const QList<QString>& lst)
  {
    QVariantList qvl;
    for (int i=0; i<lst.size(); i++)
    {
      qvl << lst.at(i);
    }
    
    return commaSepStringFromList(qvl);
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
