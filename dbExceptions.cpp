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

#include "dbExceptions.h"
#include <stdlib.h>
#include <iosfwd>
#include <string>

using namespace std;

namespace dbOverlay
{

  const char* ObjectEmptyException::what() const throw ()
  {
    string msg = "The number object ";

    if (descr != "")
    {
      msg += "'" + descr + "' ";
    }

    msg += "contained no data!";
    return msg.c_str();
  }

  const char* InvalidLogLevelException::what() const throw ()
  {
    string msg = "The logging level ";

    msg += std::to_string(lvl);

    msg += " is invalid";
    return msg.c_str();
  }

  const char* InvalidTabNameException::what() const throw ()
  {
    if (tabName.length() == 0)
    {
      string msg = "Received an invalid, empty name for a table or view!";
      return msg.c_str();
    }

    string msg = "The name '" + tabName + "' for a view or table is invalid";

    return msg.c_str();
  }
  
  const char* EmptyDatabaseHandleException::what() const throw ()
  {
    string msg = "Received a null-pointer to a database instance!";
    return msg.c_str();
  }
  
  const char* InvalidRowQualifierException::what() const throw ()
  {
    string msg = "Received an invalid qualifier / identifier to construct a new TabRow()";
    return msg.c_str();
  }
  
  const char* WriteDataFailedException::what() const throw ()
  {
    string msg = "Inserting / updating data in table " + tabName + " failed";
    return msg.c_str();
  }
}

