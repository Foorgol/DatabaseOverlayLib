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

#ifndef INTEGER_H
#define	INTEGER_H

#include "dbExceptions.h"

namespace dbOverlay {
    template <class T>
    class Item {
    public:
        Item() : _hasValue(false), myValue(T())
        {
        }

        Item(const T v) : _hasValue(true), myValue(v)
        {
        }

        Item(const Item<T>& orig) : _hasValue(false), myValue(0)
        {
            if (orig.hasValue())
            {
                myValue = orig.getValue();
                _hasValue = true;
            }
        }

        T getValue() const
        {
            if (!_hasValue)
            {
                throw ObjectEmptyException();
            }

            return myValue;
        }

        void setValue(const T newVal) {
            myValue = newVal;
            _hasValue = true;
        }

        bool hasValue() const
        {
            return _hasValue;
        }
    
    private:
        bool _hasValue;
        T myValue;
    };
    
    typedef Item<int> Integer;
    typedef Item<double> Double;
}
#endif	/* INTEGER_H */

