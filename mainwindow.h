#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "form.h";
#include "zipvcontrol.h";
#include "tools.h"
#include "open_uri.h"
#include "sign_mess.h"
#include "receiveaddresslist.h"
#include "receiveaddress_info.h"
#include "sendingaddresslist.h"
#include<QTimer>

namespace Ui {
class MainWindow;

}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);

    ~MainWindow();




    QString jGlobalparam;
    QString jAddressParam;
    QStringList jReceiveAddresses;
    QStringList jSendingAddressListOUT;


    
private slots:
    void on_pushButton_clicked();

    void on_showRequestButton_2_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_6_clicked();
    void UpdateBalance();
    void UpdateGUI();
    void onTableClicked();


    void on_pushButton_7_clicked();

    void on_actionInformation_triggered();

    void on_actionDebug_console_triggered();

    void on_actionNetwork_Monitor_triggered();

    void on_actionPeers_list_triggered();

    void on_actionWallet_Repair_triggered();

    void on_actionOpen_URI_triggered();

    void on_actionSign_message_triggered();

    void on_actionVerify_message_triggered();

    void on_actionReceiving_addresses_triggered();

    void on_actionSending_addresses_triggered();

private:
    Ui::MainWindow *ui;
    Form form;
    zipvcontrol zip;
    tools jtool;
    QTimer timer;
    Open_URI jUri;
    Sign_Mess jsign;
    Receiveaddresslist jReceive;
    ReceiveAddress_Info jReceivedAddressInfo;
    SendingAddressList jSendingAddressList;

};

#endif // MAINWINDOW_H
