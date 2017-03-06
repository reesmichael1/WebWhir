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
    ParserTests/htmlelementtests.cpp \
    ../src/parser/htmlparser.cpp \
    ../src/parser/htmltokenizer.cpp \
    ../src/parser/tokens/htmltoken.cpp \
    ../src/parser/elements/htmlelement.cpp \

HEADERS += \
    ParserTests/htmlparsertests.h \
    ParserTests/htmltokenizertests.h \
    ParserTests/htmlelementtests.h

INCLUDE += \
    ../src/main.cpp \

INCLUDEPATH += \
    ../src/parser/ \
    ../src/parser/tokens/ \
    ../src/parser/elements/

DEFINES += SRCDIR=\\\"$$PWD/\\\"
