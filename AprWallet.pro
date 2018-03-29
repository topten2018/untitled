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
    receiveaddress_info.cpp \
    dialogs/SendingAddressList.cpp \
    dialogs/OpenUri.cpp \
    dialogs/DlgAddress.cpp \
    dialogs/ReceiveAddressList.cpp \
    items/RecPayItem.cpp \
    items/AddressItem.cpp \
    models/RecPayModel.cpp \
    models/AddressBookModel.cpp \
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
    receiveaddress_info.h \
    dialogs/SendingAddressList.h \
    dialogs/OpenUri.h \
    dialogs/DlgAddress.h \
    dialogs/ReceiveAddressList.h \
    items/RecPayItem.h \
    items/AddressItem.h \
    models/RecPayModel.h \
    models/AddressBookModel.h \
    utils/AutoSaver.h \
    utils/StringUtils.h

FORMS    += ./ui/MainWindow.ui \
    ./ui/form.ui \
    ./ui/zipvcontrol.ui \
    ./ui/tools.ui \
    ./ui/OpenUri.ui \
    ./ui/sign_mess.ui \
    ./ui/DlgAddress.ui \
    ./ui/ReceiveAddressList.ui \
    ./ui/receiveaddress_info.ui \
    ./ui/SendingAddressList.ui \
    ./ui/dialog.ui \
    ./ui/RecPayItem.ui

RESOURCES += ./resources/resource.qrc
