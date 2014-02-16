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
    
    class InvalidTabNameException : public std::exception
    {
    public:
        InvalidTabNameException(string _tabName) : tabName(_tabName) {};
        InvalidTabNameException() : tabName("") {};

        virtual ~InvalidTabNameException() throw () {};
        
        const char* what() const throw ();

    private:
        string tabName;

    };
    
    class EmptyDatabaseHandleException : public std::exception
    {
    public:
        EmptyDatabaseHandleException() {};

        virtual ~EmptyDatabaseHandleException() throw () {};
        
        const char* what() const throw ();
    };
    
    class InvalidRowQualifierException : public std::exception
    {
    public:
        InvalidRowQualifierException() {};

        virtual ~InvalidRowQualifierException() throw () {};
        
        const char* what() const throw ();
    };
    
    class WriteDataFailedException : public std::exception
    {
    public:
        WriteDataFailedException(string _tabName) : tabName(_tabName) {};

        virtual ~WriteDataFailedException() throw () {};
        
        const char* what() const throw ();
    private:
      string tabName;
    };
    
}

#endif	/* OBJECTEMPTYEXCEPTION_H */

