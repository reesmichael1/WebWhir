TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -L/usr/lib/skia

SOURCES += main.cpp \
    htmlreader.cpp

HEADERS += \
    htmlreader.h

