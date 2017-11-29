#-------------------------------------------------
#
# Project created by QtCreator 2017-10-02T12:00:36
#
#-------------------------------------------------

QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

#TARGET = appEcranDyn
TEMPLATE = app


SOURCES += main.cpp\
        cihmappecrandyn.cpp \
    ctelecommanders232samsung.cpp \
    crs232c.cpp

HEADERS  += cihmappecrandyn.h \
    ctelecommanders232samsung.h \
    crs232c.h

FORMS    += cihmappecrandyn.ui
