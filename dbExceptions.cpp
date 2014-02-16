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

    msg += to_string(lvl);

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

