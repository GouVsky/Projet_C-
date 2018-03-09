#-------------------------------------------------
#
# Project created by QtCreator 2018-02-11T18:14:08
#
#-------------------------------------------------

QT       += core gui sql widgets uiplugin designer

greaterThan(QT_MAJOR_VERSION, 4): QT += core gui sql widgets uiplugin designer

TARGET = TP1
TEMPLATE += app lib
CONFIG += plugin

target.path = $$[QT_INSTALL_PLUGINS]/designer
INSTALLS += target

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
        client.cpp \
    identificationcontroller.cpp \
    addingclientcontroller.cpp \
    aproposcontroller.cpp \
    mainwindow.cpp \
    c_init_bd.cpp \
    databasecommunicator.cpp \
    searchcustomercontroller.cpp \
    resource.cpp \
    addingemployeecontroller.cpp \
    qlineeditcapitalizestring.cpp

HEADERS += \
    client.h \
    identificationcontroller.h \
    addingclientcontroller.h \
    aproposcontroller.h \
    mainwindow.h \
    c_init_bd.h \
    databasecommunicator.h \
    searchcustomercontroller.h \
    resource.h \
    addingemployeecontroller.h \
    qlineeditcapitalizestring.h


FORMS += \
        mainwindow.ui \
    identification.ui \
    apropos.ui \
    addingclient.ui \
    addingemployee.ui

RESOURCES += \
    resources.qrc

DISTFILES +=
