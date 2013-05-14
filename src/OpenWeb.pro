TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

macx {
    CONFIG -= x86_64
}

SOURCES += main.cpp \
    parser/htmlreader.cpp \
    rendernode.cpp \
    textnode.cpp \
    document.cpp

HEADERS += \
    parser/htmlreader.h \
    rendernode.h \
    textnode.h \
    document.h
