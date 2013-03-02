TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -L/usr/lib/sdl

SOURCES += main.cpp \
    htmlreader.cpp \
    rendernode.cpp \
    painter.cpp

HEADERS += \
    htmlreader.h \
    rendernode.h \
    painter.h

