#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "form.h"
#include "zipvcontrol.h"
#include "tools.h"
#include "sign_mess.h"
#include "receiveaddresslist.h"
#include "receiveaddress_info.h"
#include "sendingaddresslist.h"
#include<QTimer>

namespace Ui {
class MainWindow;

}

class RecPayModel;

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
	enum Pages {
		Overview = 0,
		Send,
		Receive,
		History,
		Privacy,
		Masternodes
	};
	
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
	
    void UpdateBalance();
    void UpdateGUI();
    void onTableClicked();

	void onSend();
	void onSendClear();
	void onAddRecipient();

    void on_actionInformation_triggered();

    void on_actionDebug_console_triggered();

    void on_actionNetwork_Monitor_triggered();

    void on_actionPeers_list_triggered();

    void on_actionWallet_Repair_triggered();

    void onOpenUri();

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
    Sign_Mess jsign;
    Receiveaddresslist jReceive;
    ReceiveAddress_Info jReceivedAddressInfo;
    SendingAddressList jSendingAddressList;

	RecPayModel * m_pRecipients;
};

#endif // MAINWINDOW_H
