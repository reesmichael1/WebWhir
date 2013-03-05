TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -L/usr/local/lib/sdl/ -lSDL

INCLUDEPATH += /usr/local/include/freetype2
INCLUDEPATH += /usr/X11/include

SOURCES += main.cpp \
    htmlreader.cpp \
    rendernode.cpp \
    painter.cpp

HEADERS += \
    htmlreader.h \
    rendernode.h \
    painter.h

