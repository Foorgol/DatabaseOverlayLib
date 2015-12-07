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

