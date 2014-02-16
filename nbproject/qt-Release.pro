# This file is generated automatically. Do not edit.
# Use project properties -> Build -> Qt -> Expert -> Custom Definitions.
TEMPLATE = lib
DESTDIR = dist/Release/CLang-Linux-x86
TARGET = DatabaseOverlayLib
VERSION = 0.1.0
CONFIG -= debug_and_release app_bundle lib_bundle
CONFIG += dll release 
PKGCONFIG +=
QT = core gui widgets sql
SOURCES += CommonTabularClass.cpp DbTab.cpp GenericDatabase.cpp HelperFunc.cpp KeyValueTab.cpp Logger.cpp TabRow.cpp dbExceptions.cpp
HEADERS += CommonTabularClass.h DbTab.h GenericDatabase.h HelperFunc.h Integer.h KeyValueTab.h Logger.h TabRow.h dbExceptions.h
FORMS +=
RESOURCES +=
TRANSLATIONS +=
OBJECTS_DIR = build/Release/CLang-Linux-x86
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
