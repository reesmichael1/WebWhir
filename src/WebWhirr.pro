QT += widgets

macx {
    CONFIG -= x86_64
}

win32 {
    RC_FILE = resources/windows/WebWhirr.rc
}

INCLUDEPATH += $$PWD

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
    painter/paintnode.cpp \
    painter/paintarea.cpp \
    elements/HTMLImgElement.cpp \
    nodes/imagenode.cpp \
    elements/HTMLHrElement.cpp \
    nodes/horizontalrulenode.cpp \
    nodes/listnode.cpp \
    elements/HTMLLiElement.cpp \
    nodes/ulnode.cpp \
    elements/HTMLUlElement.cpp \
    nodes/inode.cpp \
    elements/HTMLIElement.cpp

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
    painter/paintnode.h \
    painter/paintarea.h \
    elements/HTMLImgElement.h \
    nodes/imagenode.h \
    elements/HTMLHrElement.h \
    nodes/horizontalrulenode.h \
    nodes/listnode.h \
    elements/HTMLLiElement.h \
    nodes/ulnode.h \
    elements/HTMLUlElement.h \
    nodes/inode.h \
    elements/HTMLIElement.h
