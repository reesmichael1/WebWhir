#-------------------------------------------------
#
# Project created by QtCreator 2014-06-26T23:06:16
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = tst_parsetests
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += tst_parsetests.cpp

HEADERS += ../../../src/document.h

DEFINES += SRCDIR=\\\"$$PWD/\\\"

WEBWHIRR_SRC_DIRECTORY = ../../../src
