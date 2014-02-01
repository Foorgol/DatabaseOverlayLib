/* 
 * File:   Integer.cpp
 * Author: volker
 * 
 * Created on January 31, 2014, 9:40 PM
 */

#include "Integer.h"
#include "dbExceptions.h"

namespace dbOverlay
{

    Integer::Integer() : _hasValue(false), myValue(0)
    {
    }
    
    Integer::Integer(const int v) : _hasValue(true), myValue(v)
    {
    }

    Integer::Integer(const Integer& orig) : _hasValue(false), myValue(0)
    {
        if (orig.hasValue())
        {
            myValue = orig.getValue();
            _hasValue = true;
        }
    }
    
    int Integer::getValue() const
    {
        if (!_hasValue)
        {
            throw ObjectEmptyException();
        }
        
        return myValue;
    }
    
    void Integer::setValue(const int newVal) {
        myValue = newVal;
    }

    bool Integer::hasValue() const
    {
        return _hasValue;
    }
    
    Integer operator+(Integer lhs, const Integer& rhs)
    {
        if (!(lhs.hasValue()))
        {
            throw ObjectEmptyException("left hand side value of +-operator");
        }
        if (!(rhs.hasValue()))
        {
            throw ObjectEmptyException("right hand side value of +-operator");
        }
        
        lhs.setValue(lhs.getValue() + rhs.getValue());
        
        return lhs;
    }
}