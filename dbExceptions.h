/* 
 * File:   ObjectEmptyException.h
 * Author: volker
 *
 * Created on January 31, 2014, 9:49 PM
 */

#ifndef DBEXCEPTIONS_H
#define	DBEXCEPTIONS_H
#include <exception>
#include <string>

using namespace std;

namespace dbOverlay {

    class ObjectEmptyException : public std::exception
    {
    public:
        ObjectEmptyException() : descr("") {};
        ObjectEmptyException(string _descr) : descr(_descr) {};

        virtual ~ObjectEmptyException() throw () {};
        
        const char* what() const throw ();

    private:
        string descr;

    };
    
    class InvalidLogLevelException : public std::exception
    {
    public:
        InvalidLogLevelException(int _lvl) : lvl(_lvl) {};

        virtual ~InvalidLogLevelException() throw () {};
        
        const char* what() const throw ();

    private:
        int lvl;

    };
}

#endif	/* OBJECTEMPTYEXCEPTION_H */

