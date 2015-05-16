QT       += testlib
QT       -= gui

TARGET 	 = tests 
CONFIG   += console
CONFIG   -= app_bundle
CONFIG   += c++11

TEMPLATE = app

SOURCES += tests.cpp \
    ParserTests/htmlparsertests.cpp \
    ParserTests/htmltokenizertests.cpp \
    ../src/parser/htmlparser.cpp \
    ../src/parser/htmltokenizer.cpp

HEADERS += \
    ParserTests/htmlparsertests.h \
    ParserTests/htmltokenizertests.h \

INCLUDE += \
    ../src/main.cpp \

INCLUDEPATH += \
    ../src/parser/

DEFINES += SRCDIR=\\\"$$PWD/\\\"
