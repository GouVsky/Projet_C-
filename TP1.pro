#-------------------------------------------------
#
# Project created by QtCreator 2018-02-11T18:14:08
#
#-------------------------------------------------

QT       += core gui sql widgets uiplugin

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TP1
TEMPLATE += app
CONFIG += plugin

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
    identificationcontroller.cpp \
    mainwindow.cpp \
    c_init_bd.cpp \
    databasecommunicator.cpp \
    addingemployeecontroller.cpp \
    customer.cpp \
    editemployee.cpp \
    customizedstring.cpp \
    resource.cpp \
    type.cpp \
    addingcustomercontroller.cpp \
    aboutcontroller.cpp

HEADERS += \
    identificationcontroller.h \
    mainwindow.h \
    c_init_bd.h \
    databasecommunicator.h \
    addingemployeecontroller.h \
    customer.h \
    editemployee.h \
    customizedstring.h \
    resource.h \
    type.h \
    addingcustomercontroller.h \
    aboutcontroller.h


FORMS += \
        mainwindow.ui \
    identification.ui \
    addingemployee.ui \
    editemployee.ui \
    addingcustomer.ui \
    about.ui

RESOURCES += \
    resources.qrc


