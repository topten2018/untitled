#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_MainWindow.h"
#include "form.h"
#include "zipvcontrol.h"
#include "sign_mess.h"

#include <QSystemTrayIcon>
#include <QTimer>

class QCloseEvent;

class RecPayModel;
class AddressBookModel;
class PaymentsModel;

class ReceiveAddressList;
class SendingAddressList;
class Tools;

struct WalletSettings 
{
	bool m_bEnableCoinControl;
	bool m_bShowMasterNodes;
	bool m_bSpendUnconfirmedChange;

	WalletSettings() : m_bEnableCoinControl{ false }, m_bShowMasterNodes{ false }, m_bSpendUnconfirmedChange{ false }
	{
	}
};
struct WindowSettings
{
	bool m_bMinimizeToTray;
	bool m_bHideOnClose;

	WindowSettings() : m_bMinimizeToTray{ false }, m_bHideOnClose{ false }
	{
	}
};


class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    enum Pages 
	{
		Overview = 0,
		Send,
		Receive,
		History,
		Privacy,
		Masternodes,
		Count
	};
	
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

    QString jGlobalparam;        
private slots:
    void onAutoMN();
	void loadSettings();

	void onMultisignatureCreation();
	void onMultisignatureSpending();
	void onMultisignatureSigning();

	void onEncryptWallet();
	void onChangePassphrase();
	
    void on_showRequestButton_2_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_11_clicked();
	
    void UpdateBalance();
    void UpdateGUI();
    void onStaking();
	void onBackupWallet();
    
	void onOverviewPage();
	void onSendPage();
	void onReceivePage();
	void onTransactionsPage();
	void onPrivacyPage();
	void onMasternodesPage();

	void onSend();
	void onSendClear();
	void onAddRecipient();
	void onShowHideFeeInfo();
	void onChangeFee();

	void onRequestPayment();
	void onReceiveClear();
	void onShowPaymentInfo();
	void onDeletePayment();
	void updatePaymentButtons();
	
	void onShowAutomaticBackups();

    void on_actionInformation_triggered();

    void on_actionDebug_console_triggered();

    void on_actionNetwork_Monitor_triggered();

    void on_actionPeers_list_triggered();

    void on_actionWallet_Repair_triggered();

    void onOpenUri();
	void onSendingAddresses();
	void onReceivingAddresses();
	void onSettings();
	void onQuit();
	void onShowHide();
	void iconActivated(QSystemTrayIcon::ActivationReason reason);

    void on_actionSign_message_triggered();

    void on_actionVerify_message_triggered(); 
private:
	virtual void closeEvent(QCloseEvent *) override;
	virtual void changeEvent(QEvent* e) override;
	void createTrayIcon();

	QString createAddress() const;

    Ui::MainWindow ui;

    Form form;
    zipvcontrol zip;
    QTimer timer;
    Sign_Mess jsign;

	bool				  m_bStake;

	RecPayModel			* m_pRecipients;
	AddressBookModel	* m_pSendingAddressBook;
	AddressBookModel	* m_pReceiveAddressBook;
	PaymentsModel		* m_pPaymentsHistory;

	ReceiveAddressList * m_pDlgReceiveAddressList;
	SendingAddressList * m_pDlgSendingAddressList;
    Tools			   * m_pDlgTool;

	QSystemTrayIcon		*m_pSysTrayIcon;
	QMenu				*m_pTrayMenu;

	QWidget				*m_pMasternodesTab;

	WindowSettings		 m_sWindowSettings;
	WalletSettings		 m_sWalletSettings;

	QString				 m_strPublicAddress;
	QString				 m_strPrivateAddress;
};

#endif // MAINWINDOW_H
