QT       += testlib
QT       -= gui

TARGET 	 = tests 
CONFIG   += console
CONFIG   -= app_bundle

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
