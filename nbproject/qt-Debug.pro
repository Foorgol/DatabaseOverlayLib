# This file is generated automatically. Do not edit.
# Use project properties -> Build -> Qt -> Expert -> Custom Definitions.
TEMPLATE = lib
DESTDIR = dist/Debug/CLang-Linux-x86
TARGET = DatabaseOverlayLib
VERSION = 1.0.0
CONFIG -= debug_and_release app_bundle lib_bundle
CONFIG += dll debug 
PKGCONFIG +=
QT = core gui widgets sql
SOURCES += BasicTestClass.cpp CommonTabularClass.cpp DatabaseTestScenario.cpp DbTab.cpp GenericDatabase.cpp HelperFunc.cpp Logger.cpp SampleDB.cpp TabRow.cpp dbExceptions.cpp tstCommonTabularClass.cpp tstGenericDatabase.cpp tstTabRow.cpp
HEADERS += BasicTestClass.h CommonTabularClass.h DatabaseTestScenario.h DbTab.h GenericDatabase.h HelperFunc.h Integer.h Logger.h SampleDB.h TabRow.h dbExceptions.h tstCommonTabularClass.h tstGenericDatabase.h tstTabRow.h
FORMS +=
RESOURCES +=
TRANSLATIONS +=
OBJECTS_DIR = build/Debug/CLang-Linux-x86
MOC_DIR = 
RCC_DIR = 
UI_DIR = 
QMAKE_CC = clang
QMAKE_CXX = clang++
DEFINES += 
INCLUDEPATH += 
LIBS += 
equals(QT_MAJOR_VERSION, 4) {
QMAKE_CXXFLAGS += -std=c++11
}
equals(QT_MAJOR_VERSION, 5) {
CONFIG += c++11
}
