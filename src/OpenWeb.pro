TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += /usr/local/include
DEPENDPATH += /usr/local/include

QMAKE_CXXFLAGS += -std=gnu++0x

LIBS += -L/usr/local/lib/SFML/

LIBS += -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-window -lsfml-system

SOURCES += main.cpp \
    htmlreader.cpp \
    rendernode.cpp \
    painter.cpp \
    textnode.cpp \
    coloroperations.cpp \
    document.cpp

HEADERS += \
    htmlreader.h \
    rendernode.h \
    painter.h \
    textnode.h \
    coloroperations.h \
    document.h
