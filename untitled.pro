#-------------------------------------------------
#
# Project created by QtCreator 2018-03-08T02:35:57
#
#-------------------------------------------------

QT       += core gui
QT += network
TARGET = untitled
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    d.cpp \
    form.cpp \
    zipvcontrol.cpp \
    sockettest.cpp \
    worker.cpp \
    tools.cpp \
    open_uri.cpp \
    sign_mess.cpp \
    receiveaddresslist.cpp \
    receiveaddress_info.cpp \
    sendingaddresslist.cpp \
    newsendingaddress.cpp

HEADERS  += mainwindow.h \
    d.h \
    dialog.h \
    form.h \
    zipvcontrol.h \
    sockettest.h \
    worker.h \
    tools.h \
    open_uri.h \
    sign_mess.h \
    receiveaddresslist.h \
    receiveaddress_info.h \
    sendingaddresslist.h \
    newsendingaddress.h

FORMS    += mainwindow.ui \
    form.ui \
    zipvcontrol.ui \
    tools.ui \
    open_uri.ui \
    sign_mess.ui \
    receiveaddresslist.ui \
    receiveaddress_info.ui \
    sendingaddresslist.ui \
    newsendingaddress.ui
FORMS  +=   dialog.ui

RESOURCES += \
    resource.qrc
