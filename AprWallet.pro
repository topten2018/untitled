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
    dialogs/SendingAddressList.cpp \
    dialogs/OpenUri.cpp \
    dialogs/DlgAddress.cpp \
    dialogs/ReceiveAddressList.cpp \
    dialogs/ReceiveAddressInfo.cpp \
    dialogs/DlgSettings.cpp \
    items/RecPayItem.cpp \
    items/AddressItem.cpp \
    items/TransactionItem.cpp\
    models/RecPayModel.cpp \
    models/AddressBookModel.cpp \
    models/PaymentsModel.cpp\
    utils/AutoSaver.cpp \
    utils/StringUtils.cpp \
    utils/FileUtils.cpp \
    utils/QrEncoder.cpp \
    widgets/QrCodeImage.cpp \
    WalletStorage.cpp

HEADERS  += MainWindow.h \
    d.h \
    dialog.h \
    form.h \
    zipvcontrol.h \
    sockettest.h \
    worker.h \
    tools.h \
    sign_mess.h \
    dialogs/SendingAddressList.h \
    dialogs/OpenUri.h \
    dialogs/DlgAddress.h \
    dialogs/ReceiveAddressList.h \
    dialogs/ReceiveAddressInfo.h \
    dialogs/DlgSettings.h \
    items/RecPayItem.h \
    items/AddressItem.h \
    items/TransactionItem.h \
    models/RecPayModel.h \
    models/AddressBookModel.h \
    models/PaymentsModel.h \
    utils/AutoSaver.h \
    utils/StringUtils.h \
    utils/QrEncoder.h \
    utils/FileUtils.h \
    widgets/QrCodeImage.h \
    WalletStorage.h

FORMS    += ./ui/MainWindow.ui \
    ./ui/form.ui \
    ./ui/zipvcontrol.ui \
    ./ui/tools.ui \
    ./ui/OpenUri.ui \
    ./ui/sign_mess.ui \
    ./ui/DlgAddress.ui \
    ./ui/ReceiveAddressList.ui \
    ./ui/SendingAddressList.ui \
    ./ui/dialog.ui \
    ./ui/RecPayItem.ui \
    ./ui/ReceiveAddressInfo.ui \
    ./ui/DlgSettings.ui

RESOURCES += ./resources/resource.qrc
