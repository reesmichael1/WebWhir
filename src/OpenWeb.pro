TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

LIBS += /usr/local/lib -sfml-audio.2.0
LIBS += /usr/local/lib -sfml-audio.2
LIBS += /usr/local/lib -sfml-audio
LIBS += /usr/local/lib -sfml-graphics.2.0
LIBS += /usr/local/lib -sfml-graphics.2
LIBS += /usr/local/lib -sfml-graphics
LIBS += /usr/local/lib -sfml-network.2.0
LIBS += /usr/local/lib -sfml-network.2
LIBS += /usr/local/lib -sfml-network
LIBS += /usr/local/lib -sfml-system.2.0
LIBS += /usr/local/lib -sfml-system.2
LIBS += /usr/local/lib -sfml-system
LIBS += /usr/local/lib -sfml-window.2.0
LIBS += /usr/local/lib -sfml-window.2
LIBS += /usr/local/lib -sfml-window

INCLUDEPATH += /usr/local/include/

SOURCES += main.cpp \
    htmlreader.cpp \
    rendernode.cpp \
    painter.cpp

HEADERS += \
    htmlreader.h \
    rendernode.h \
    painter.h
