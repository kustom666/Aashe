#-------------------------------------------------
#
# Project created by QtCreator 2014-02-25T18:17:14
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Aashe
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    highlighters/cpphighlighter.cpp

HEADERS  += mainwindow.h \
    highlighters/cpphighlighter.h

FORMS    += mainwindow.ui
