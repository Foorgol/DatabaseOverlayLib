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

