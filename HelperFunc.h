/* 
 * File:   HelperFunc.h
 * Author: volker
 *
 * Created on February 2, 2014, 10:31 AM
 */

#ifndef HELPERFUNC_H
#define	HELPERFUNC_H

#include <string>
#include <QtCore>
#include <QList>
#include <QVariant>

using namespace std;

namespace dbOverlay
{
  const string QString2String(const QString &inString);
  
  QString commaSepStringFromList(const QList<QString>& lst);
  QString commaSepStringFromList(const QVariantList& lst);
}
#endif	/* HELPERFUNC_H */

