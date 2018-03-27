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
    sign_mess.cpp \
    receiveaddresslist.cpp \
    receiveaddress_info.cpp \
    sendingaddresslist.cpp \
    newsendingaddress.cpp \
    dialogs\OpenUri.cpp \
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
    sign_mess.h \
    receiveaddresslist.h \
    receiveaddress_info.h \
    sendingaddresslist.h \
    newsendingaddress.h \
    dialogs\OpenUri.h \
    items\RecPayItem.h \
    models\RecPayModel.h

FORMS    += ./ui/mainwindow.ui \
    ./ui/form.ui \
    ./ui/zipvcontrol.ui \
    ./ui/tools.ui \
    ./ui/OpenUri.ui \
    ./ui/sign_mess.ui \
    ./ui/receiveaddresslist.ui \
    ./ui/receiveaddress_info.ui \
    ./ui/sendingaddresslist.ui \
    ./ui/newsendingaddress.ui \
    ./ui/dialog.ui \
    ./ui/RecPayItem.ui

RESOURCES += ./resources/resource.qrc
