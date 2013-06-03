TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

macx {
    CONFIG -= x86_64
}

SOURCES += main.cpp \
    parser/htmlreader.cpp \
    nodes/rendernode.cpp \
    document.cpp \
    elements/HTMLHeadElement.cpp \
    elements/HTMLElement.cpp \
    elements/HTMLBodyElement.cpp \
    nodes/bodynode.cpp \
    nodes/headnode.cpp \
    elements/HTMLBElement.cpp \
    nodes/bnode.cpp \
    nodes/paragraphnode.cpp \
    elements/HTMLParagraphElement.cpp

HEADERS += \
    parser/htmlreader.h \
    nodes/rendernode.h \
    document.h \
    elements/HTMLHeadElement.h \
    elements/HTMLElement.h \
    elements/HTMLBodyElement.h \
    nodes/bodynode.h \
    nodes/headnode.h \
    elements/HTMLBElement.h \
    nodes/bnode.h \
    nodes/paragraphnode.h \
    elements/HTMLParagraphElement.h
