#-------------------------------------------------
#
# Project created by QtCreator 2015-07-12T15:43:44
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Agenda
TEMPLATE = app

CONFIG += c++11

SOURCES += \
    src/main.cpp \
    src/Core/AgendaService.cpp \
    src/Core/Date.cpp \
    src/Core/Meeting.cpp \
    src/Core/Storage.cpp \
    src/Core/User.cpp \
    src/GUI/mainwindow.cpp \
    src/GUI/logindialog.cpp \
    src/Core/utils.cpp \
    src/GUI/notifybar.cpp \
    src/Core/logger.cpp \
    src/GUI/modelgetter.cpp \
    src/GUI/createmeetingdialog.cpp \
    src/GUI/dateselectdialog.cpp

HEADERS += \
    src/Core/AgendaService.h \
    src/Core/Date.h \
    src/Core/Meeting.h \
    src/Core/Storage.h \
    src/Core/User.h \
    src/GUI/mainwindow.h \
    src/GUI/logindialog.h \
    src/Core/utils.h \
    src/GUI/notifybar.h \
    src/Core/logger.h \
    src/GUI/modelgetter.h \
    src/GUI/createmeetingdialog.h \
    src/GUI/dateselectdialog.h

