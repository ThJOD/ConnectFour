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
    GUI/gamestartdialog.cpp \
    GUI/gamewindow.cpp \
    GUI/mainwindow.cpp \
    Logic/gamehandler.cpp \
    Logic/gamereplayer.cpp \
    Logic/gamesimulator.cpp \
    Logic/humanplayer.cpp \
    Logic/networkplayer.cpp \
    Logic/player.cpp \
    GUI/field.cpp \
    GUI/chip.cpp

HEADERS  += \
    GUI/gamestartdialog.h \
    GUI/gamewindow.h \
    GUI/mainwindow.h \
    Logic/gamehandler.h \
    Logic/gamereplayer.h \
    Logic/gamesimulator.h \
    Logic/humanplayer.h \
    Logic/networkplayer.h \
    Logic/player.h \
    GUI/field.h \
    GUI/chip.h

FORMS += \
    GUI/mainwindow.ui


textures.files = textures/*
textures.path = $$OUT_PWD/textures/
INSTALLS += textures
