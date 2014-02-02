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

namespace dbOverlay {
    
    const char* ObjectEmptyException::what() const throw () {
        string msg = "The number object ";
        
        if (descr != "")
        {
            msg += "'" + descr + "' ";
        }
        
        msg += "contained no data!";
        return msg.c_str();
    }
}

