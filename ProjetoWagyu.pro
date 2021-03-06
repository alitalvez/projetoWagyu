#-------------------------------------------------
#
# Project created by QtCreator 2016-08-16T15:13:45
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ProjetoWagyu
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    imgloader.cpp \
    hex2int.cxx \
    readimage.cpp \
    haralick.cpp \
    guimatrizcoo.cpp

HEADERS  += mainwindow.h \
    imgloader.h \
    hex2int.h \
    globalvar.h \
    readimage.h \
    haralick.h \
    guimatrizcoo.h

FORMS    += mainwindow.ui \
    guimatrizcoo.ui

QMAKE_CXXFLAGS += -fopenmp
QMAKE_CFLAGS_RELEASE += -fopenmp
QMAKE_CFLAGS_DEBUG += -fopenmp
LIBS += -fopenmp

