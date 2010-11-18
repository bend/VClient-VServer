#-------------------------------------------------
#
# Project created by QtCreator 2010-11-06T17:31:29
#
#-------------------------------------------------

QT       += core gui
QT       += network

TARGET = VClient
TEMPLATE = app


SOURCES += main.cpp\
        vclientwindow.cpp \
    client.cpp \
    screenshareview.cpp \
    vclientview.cpp \
    filetree.cpp

HEADERS  += vclientwindow.h \
    client.h \
    Constants.h \
    screenshareview.h \
    vclientview.h \
    filetree.h

FORMS    += vclientwindow.ui
