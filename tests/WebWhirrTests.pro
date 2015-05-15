QT       += testlib
QT       -= gui

TARGET 	 = tests 
CONFIG   += console
CONFIG   -= app_bundle
CONFIG   += c++11

TEMPLATE = app

SOURCES += tests.cpp \
    ParserTests/htmlparsertests.cpp \
    ../src/parser/htmlparser.cpp

HEADERS += \
    ParserTests/htmlparsertests.h \

INCLUDE += \
    ../src/main.cpp \

INCLUDEPATH += \
    ../src/parser/

DEFINES += SRCDIR=\\\"$$PWD/\\\"
