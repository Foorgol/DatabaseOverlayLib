/* 
 * File:   Integer.h
 * Author: volker
 *
 * Created on January 31, 2014, 9:40 PM
 */

#ifndef INTEGER_H
#define	INTEGER_H

namespace dbOverlay {
    class Integer {
    public:
        Integer();
        Integer(const Integer& orig);
        Integer(int v);
        int getValue() const;
        void setValue(const int newVal);
        bool hasValue() const;
        
        //Integer operator+(Integer lhs, const Integer& rhs);

    private:
        bool _hasValue;
        int myValue;
    };
}
#endif	/* INTEGER_H */

