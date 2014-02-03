#-------------------------------------------------
#
# Project created by QtCreator 2014-01-08T12:29:38
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtCodeSample
TEMPLATE = app


SOURCES += main.cpp\
        codesamplewindow.cpp \
    wallmodel.cpp \
    lengthnode.cpp

HEADERS  += codesamplewindow.h \
    wallmodel.h \
    lengthnode.h

FORMS    += codesamplewindow.ui

OTHER_FILES +=

RESOURCES += \
    icons.qrc
