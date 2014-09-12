#-------------------------------------------------
#
# Project created by QtCreator 2014-09-12T13:04:40
#
#-------------------------------------------------

QT       += sql

QT       -= gui

TARGET = DatabaseOverlayLib
TEMPLATE = lib
QMAKE_CXXFLAGS += -std=c++11

unix {
    target.path = /usr/lib
    INSTALLS += target
}

HEADERS += \
    CommonTabularClass.h \
    dbExceptions.h \
    DbTab.h \
    GenericDatabase.h \
    HelperFunc.h \
    Integer.h \
    KeyValueTab.h \
    Logger.h \
    SampleDB.h \
    TabRow.h

SOURCES += \
    CommonTabularClass.cpp \
    dbExceptions.cpp \
    DbTab.cpp \
    GenericDatabase.cpp \
    HelperFunc.cpp \
    KeyValueTab.cpp \
    Logger.cpp \
    SampleDB.cpp \
    TabRow.cpp
