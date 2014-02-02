/* 
 * File:   Integer.h
 * Author: volker
 *
 * Created on January 31, 2014, 9:40 PM
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

