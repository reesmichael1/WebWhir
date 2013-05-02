TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += /usr/local/include
DEPENDPATH += /usr/local/include

macx {
    CONFIG -= x86_64
}

LIBS += -L/usr/local/lib/SFML/

CONFIG(release, debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-window -lsfml-system
CONFIG(debug, debug|release): LIBS += -lsfml-audio-d -lsfml-graphics-d -lsfml-network-d -lsfml-window-d -lsfml-system-d

SOURCES += main.cpp \
    parser/htmlreader.cpp \
    rendernode.cpp \
    painter.cpp \
    textnode.cpp \
    coloroperations.cpp \
    document.cpp

HEADERS += \
    parser/htmlreader.h \
    rendernode.h \
    painter.h \
    textnode.h \
    coloroperations.h \
    document.h
