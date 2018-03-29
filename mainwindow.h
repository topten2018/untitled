#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_MainWindow.h"
#include "form.h"
#include "zipvcontrol.h"
#include "tools.h"
#include "sign_mess.h"
#include "receiveaddress_info.h"
#include <QTimer>

class RecPayModel;
class AddressBookModel;

class ReceiveAddressList;
class SendingAddressList;

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
	void onShowHideFeeInfo();
	void onChangeFee();

    void on_actionInformation_triggered();

    void on_actionDebug_console_triggered();

    void on_actionNetwork_Monitor_triggered();

    void on_actionPeers_list_triggered();

    void on_actionWallet_Repair_triggered();

    void onOpenUri();
	void onSendingAddresses();
	void onReceivingAddresses();

    void on_actionSign_message_triggered();

    void on_actionVerify_message_triggered();


    

private:
    Ui::MainWindow ui;

    Form form;
    zipvcontrol zip;
    tools jtool;
    QTimer timer;
    Sign_Mess jsign;
    ReceiveAddress_Info jReceivedAddressInfo;

	RecPayModel		* m_pRecipients;
	AddressBookModel * m_pSendingAddressBook;
	AddressBookModel * m_pReceiveAddressBook;

	ReceiveAddressList * m_pDlgReceiveAddressList;
	SendingAddressList * m_pDlgSendingAddressList;
};

#endif // MAINWINDOW_H
