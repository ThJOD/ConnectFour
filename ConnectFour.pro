#-------------------------------------------------
#
# Project created by QtCreator 2016-06-26T18:15:01
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ConnectFour
TEMPLATE = app


SOURCES += main.cpp \
    mainwindow.cpp \
    gamehandler.cpp \
    gamewindow.cpp \
    player.cpp \
    gamestartdialog.cpp \
    gamesimulator.cpp \
    gamereplayer.cpp \
    networkplayer.cpp \
    humanplayer.cpp

HEADERS  += \
    mainwindow.h \
    gamehandler.h \
    gamewindow.h \
    player.h \
    gamestartdialog.h \
    gamesimulator.h \
    gamereplayer.h \
    networkplayer.h \
    humanplayer.h

FORMS += \
    mainwindow.ui
