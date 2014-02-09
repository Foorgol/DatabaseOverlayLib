/* 
 * File:   ObjectEmptyException.cpp
 * Author: volker
 * 
 * Created on January 31, 2014, 9:49 PM
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
}

