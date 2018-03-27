#-------------------------------------------------
#
# Project created by QtCreator 2018-03-08T02:35:57
#
#-------------------------------------------------

TEMPLATE = app
QT += core gui network widgets
TARGET = untitled

INCLUDEPATH += ./GeneratedFiles \
    . \
    ./GeneratedFiles
DEPENDPATH += .
MOC_DIR += ./GeneratedFiles

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
    newsendingaddress.cpp \
    items\RecPayItem.cpp \
    models\RecPayModel.cpp	

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
    newsendingaddress.h \
    items\RecPayItem.h \
    models\RecPayModel.h

FORMS    += ./ui/mainwindow.ui \
    ./ui/form.ui \
    ./ui/zipvcontrol.ui \
    ./ui/tools.ui \
    ./ui/open_uri.ui \
    ./ui/sign_mess.ui \
    ./ui/receiveaddresslist.ui \
    ./ui/receiveaddress_info.ui \
    ./ui/sendingaddresslist.ui \
    ./ui/newsendingaddress.ui \
    ./ui/dialog.ui \
    ./ui/RecPayItem.ui

RESOURCES += ./resources/resource.qrc
