# This file is generated automatically. Do not edit.
# Use project properties -> Build -> Qt -> Expert -> Custom Definitions.
TEMPLATE = app
DESTDIR = dist/UnitTesting/CLang-Linux-x86
TARGET = DatabaseOverlayLib
VERSION = 1.0.0
CONFIG -= debug_and_release app_bundle lib_bundle
CONFIG += debug 
PKGCONFIG +=
QT = core gui widgets sql
SOURCES += BasicTestClass.cpp CommonTabularClass.cpp DatabaseTestScenario.cpp DbTab.cpp GenericDatabase.cpp HelperFunc.cpp KeyValueTab.cpp Logger.cpp SampleDB.cpp TabRow.cpp dbExceptions.cpp tstCommonTabularClass.cpp tstDbTab.cpp tstGenericDatabase.cpp tstHelperFunc.cpp tstInteger.cpp tstKeyValueTab.cpp tstTabRow.cpp unitTestMain.cpp
HEADERS += BasicTestClass.h CommonTabularClass.h DatabaseTestScenario.h DbTab.h GenericDatabase.h HelperFunc.h Integer.h KeyValueTab.h Logger.h SampleDB.h TabRow.h dbExceptions.h tstCommonTabularClass.h tstDbTab.h tstGenericDatabase.h tstHelperFunc.h tstInteger.h tstKeyValueTab.h tstTabRow.h
FORMS +=
RESOURCES +=
TRANSLATIONS +=
OBJECTS_DIR = build/UnitTesting/CLang-Linux-x86
MOC_DIR = 
RCC_DIR = 
UI_DIR = 
QMAKE_CC = clang
QMAKE_CXX = clang++
DEFINES += 
INCLUDEPATH += 
LIBS += -lcppunit -ldl  
equals(QT_MAJOR_VERSION, 4) {
QMAKE_CXXFLAGS += -std=c++11
}
equals(QT_MAJOR_VERSION, 5) {
CONFIG += c++11
}
