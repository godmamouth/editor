#-------------------------------------------------
#
# Project created by QtCreator 2016-02-25T12:30:23
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = IFCEdit
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    node.cpp \
    nodesmanager.cpp \
    filemanager.cpp \
    removenodesbytypewidget.cpp \
    ifcbrowser.cpp \
    ifceditmanager.cpp \
    progressbarmanager.cpp \
    modification.cpp

HEADERS  += mainwindow.h \
    node.h \
    nodesmanager.h \
    filemanager.h \
    removenodesbytypewidget.h \
    ifcbrowser.h \
    ifceditmanager.h \
    progressbarmanager.h \
    modification.h

FORMS    += mainwindow.ui \
    removenodesbytypewidget.ui \
    find.ui
