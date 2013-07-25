QT += widgets

macx {
    CONFIG -= x86_64
}

win32 {
    RC_FILE = resources/windows/WebWhirr.rc
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
    elements/HTMLParagraphElement.cpp \
    interface/mainwindow.cpp \
    painter/painter.cpp \
    painter/paintnode.cpp

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
    elements/HTMLParagraphElement.h \
    interface/mainwindow.h \
    painter/painter.h \
    painter/paintnode.h
