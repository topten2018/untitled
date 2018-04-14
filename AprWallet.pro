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
    sign_mess.cpp \
    dialogs/SendingAddressList.cpp \
    dialogs/OpenUri.cpp \
    dialogs/DlgAddress.cpp \
    dialogs/ReceiveAddressList.cpp \
    dialogs/ReceiveAddressInfo.cpp \
    dialogs/DlgSettings.cpp \
    dialogs/DlgAskPassphrase.cpp \
    dialogs/DlgMultisignature.cpp \
    dialogs/Tools.cpp \
    dialogs/DlgMultisignature.cpp \
    items/RecPayItem.cpp \
    items/AddressItem.cpp \
    items/TransactionItem.cpp \
    items/AddressKeyItem.cpp \
    items/DestinationItem.cpp \
    items/KeyItem.cpp \
    items/TxHashItem.cpp \
    utils/AutoSaver.cpp \
    utils/StringUtils.cpp \
    utils/FileUtils.cpp \
    utils/QrEncoder.cpp \
    widgets/QrCodeImage.cpp \
    WalletStorage.cpp \
    models/AddressBookModel.cpp \
    models/AddressKeyModel.cpp \
    models/DestinationModel.cpp \
    models/KeyModel.cpp \
    models/PaymentsModel.cpp \
    models/RecPayModel.cpp \
    models/TxHashModel.cpp \
    dialogs/DlgMultisend.cpp \
    dialogs/DlgBip38Tool.cpp \
    dialogs/DlgBlockchainExplorer.cpp

HEADERS  += MainWindow.h \
    d.h \
    dialog.h \
    form.h \
    zipvcontrol.h \
    sockettest.h \
    worker.h \
    sign_mess.h \
    dialogs/SendingAddressList.h \
    dialogs/OpenUri.h \
    dialogs/DlgAddress.h \
    dialogs/ReceiveAddressList.h \
    dialogs/ReceiveAddressInfo.h \
    dialogs/DlgSettings.h \
    dialogs/DlgAskPassphrase.h \
    dialogs/DlgMultisignature.h \
    dialogs/Tools.h \
    items/RecPayItem.h \
    items/AddressItem.h \
    items/TransactionItem.h \
    items/AddressKeyItem.h \
    items/DestinationItem.h \
    items/KeyItem.h \
    items/TxHashItem.h \
    utils/AutoSaver.h \
    utils/StringUtils.h \
    utils/QrEncoder.h \
    utils/FileUtils.h \
    widgets/QrCodeImage.h \
    WalletStorage.h \
    dialogs/DlgMultisignature.h \
    models/AddressBookModel.h \
    models/AddressKeyModel.h \
    models/DestinationModel.h \
    models/KeyModel.h \
    models/PaymentsModel.h \
    models/RecPayModel.h \
    models/TxHashModel.h \
    dialogs/DlgMultisend.h \
    dialogs/DlgBip38Tool.h \
    dialogs/DlgBlockchainExplorer.h

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
    ./ui/DlgSettings.ui \
    ui/AddressKeyItem.ui \
    ui/DestinationItem.ui \
    ui/DlgAskPassphrase.ui \
    ui/DlgMultisignature.ui \
    ui/KeyItem.ui \
    ui/Tools.ui \
    ui/TxHashItem.ui \
    ui/DlgMultisend.ui \
    ui/DlgBip38Tool.ui \
    ui/DlgBlockchainExplorer.ui

RESOURCES += ./resources/resource.qrc
