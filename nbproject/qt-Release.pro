# This file is generated automatically. Do not edit.
# Use project properties -> Build -> Qt -> Expert -> Custom Definitions.
TEMPLATE = lib
DESTDIR = dist/Release/CLang-Linux-x86
TARGET = DatabaseOverlayLib
VERSION = 1.0.0
CONFIG -= debug_and_release app_bundle lib_bundle
CONFIG += dll release 
PKGCONFIG +=
QT = core gui widgets
SOURCES += dbExceptions.cpp tstInteger.cpp unitTestMain.cpp
HEADERS += Integer.h dbExceptions.h tstInteger.h
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
