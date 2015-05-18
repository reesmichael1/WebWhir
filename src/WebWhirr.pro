TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG += c++11

SOURCES += \
    main.cpp \
    parser/htmlparser.cpp \
    parser/htmltokenizer.cpp \
    parser/tokens/htmltoken.cpp

HEADERS += \
    parser/htmlparser.h \
    parser/htmltokenizer.h \
    parser/tokens/htmltoken.h

