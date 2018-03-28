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
    MainWindow.cpp \
    d.cpp \
    form.cpp \
    zipvcontrol.cpp \
    sockettest.cpp \
    worker.cpp \
    tools.cpp \
    sign_mess.cpp \
    receiveaddresslist.cpp \
    receiveaddress_info.cpp \
    newsendingaddress.cpp \
    dialogs/SendingAddressList.cpp \
    dialogs/OpenUri.cpp \
    dialogs/DlgAdress.cpp \
    items/RecPayItem.cpp \
    items/AdressItem.cpp \
    models/RecPayModel.cpp \
    models/AdressBookModel.cpp \
    utils/AutoSaver.cpp \
    utils/StringUtils.cpp

HEADERS  += MainWindow.h \
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
    newsendingaddress.h \
    dialogs/SendingAddressList.h \
    dialogs/OpenUri.h \
    dialogs/DlgAdress.h \
    items/RecPayItem.h \
    items/AdressItem.h \
    models/RecPayModel.h \
    models/AdressBookModel.h \
    utils/AutoSaver.h \
    utils/StringUtils.h

FORMS    += ./ui/MainWindow.ui \
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
