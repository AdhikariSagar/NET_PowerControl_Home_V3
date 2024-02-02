#-------------------------------------------------
#
# Project created by QtCreator 2023-03-08T11:22:53
#
#-------------------------------------------------

QT       += core gui network widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = NET_PowerControl_Home_V3
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
        connection_dialog.cpp \
        discovery_dialog.cpp \
        login_dialog.cpp \
        main.cpp \
        mainwindow.cpp \
        power_supply.cpp \
        powersupplydiscovery.cpp \
        server.cpp

HEADERS += \
        connection_dialog.h \
        discovery_dialog.h \
        localipfinder.h \
        login_dialog.h \
        mainwindow.h \
        power_supply.h \
        powercontrolinfo.h \
        powersupplydiscovery.h \
        server.h

FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

DISTFILES +=
