#-------------------------------------------------
#
# Project created by QtCreator 2018-12-26T13:05:27
#
#-------------------------------------------------

QT       += core gui charts axcontainer
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Wykresy2
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    wykreskolowy.cpp \
    globals.cpp \
    wykres.cpp \
    wykresliniowy.cpp \
    eksplorator.cpp \
    logowanie.cpp \
    opiswykres.cpp \
    request.cpp \
    info.cpp \
    problem.cpp \
    github.cpp \
    qtinfo.cpp

HEADERS += \
        mainwindow.h \
    wykreskolowy.h \
    globals.h \
    wykres.h \
    wykresliniowy.h \
    eksplorator.h \
    logowanie.h \
    opiswykres.h \
    request.h \
    info.h \
    problem.h \
    github.h \
    qtinfo.h

FORMS += \
        mainwindow.ui \
    wykreskolowy.ui \
    wykres.ui \
    wykresliniowy.ui \
    eksplorator.ui \
    logowanie.ui \
    opiswykres.ui \
    request.ui \
    info.ui \
    problem.ui \
    github.ui \
    qtinfo.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images.qrc \
    icons.qrc \
    style.qrc \
    images.qrc \
    icons.qrc \
    style.qrc
