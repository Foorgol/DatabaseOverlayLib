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
  
  QString commaSepStringFromList(const QStringList& lst);
  QString commaSepStringFromList(const QVariantList& lst);
  QVariantList prepWhereClause(const QVariantList& params);
}
#endif	/* HELPERFUNC_H */

