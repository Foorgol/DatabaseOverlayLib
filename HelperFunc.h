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

