#include "MainWindow.h"
#include <QMessageBox>
#include <QTabWidget>
#include <QTabBar>
#include <QRegExp>
#include <QTcpSocket>
#include <QDebug>
#include <QHBoxLayout>
#include <QDialog>
#include <QString>
#include <QSettings>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QStringList>
#include <QDate>
#include <QFile>
#include <QTextStream>
#include <QTimer>
#include <QThread>
#include <QDebug>
#include <QDir>
#include <QCloseEvent>
#include <QHeaderView>
#include <QFileDialog>
#include <QProcessEnvironment>
#include <QDesktopServices>
#include <QTime>

#include <cmath>

#include "dialog.h"
#include "sockettest.h"
#include "worker.h"
#include "models/RecPayModel.h"
#include "models/AddressBookModel.h"
#include "models/PaymentsModel.h"

#include "items/TransactionItem.h"

#include "dialogs/OpenUri.h"
#include "dialogs/SendingAddressList.h"
#include "dialogs/ReceiveAddressList.h"
#include "dialogs/DlgSettings.h"
#include "dialogs/ReceiveAddressInfo.h"
#include "dialogs/Tools.h"
#include "dialogs/DlgMultisignature.h"
#include "dialogs/DlgAskPassphrase.h"
#include "dialogs/DlgBip38Tool.h"
#include "dialogs/DlgMultisend.h"
#include "dialogs/DlgBlockchainExplorer.h"

#include "utils/StringUtils.h"
#include "utils/FileUtils.h"

#include "WalletStorage.h"

int jTotalBalance=0;
QString jGlobalparam = "";

QString s_exeLocation;

MainWindow::MainWindow(QWidget *parent) 
	: QMainWindow(parent)
	, m_bStake(false)
{
	qsrand(time(NULL));

	// Define the base location - Should be ended with a slash!
	s_exeLocation = QCoreApplication::arguments()[0];
	int i = s_exeLocation.lastIndexOf(QDir::separator());
	if (i == -1)
		s_exeLocation = "";
	else
		s_exeLocation = s_exeLocation.left(i + 1);

	QCoreApplication::setOrganizationName(QLatin1String("AprWallet"));
	QCoreApplication::setApplicationName(QLatin1String("APR Wallet Version 1.0"));
	QCoreApplication::setApplicationVersion(QLatin1String("0.0.1"));
	
	Utils::createDir(s_exeLocation, "backups");
	
	ui.setupUi(this);
	
	WalletStorage ws;
	QString fname = s_exeLocation + tr("backups/AprWallet.dat") + QDateTime::currentDateTime().toString("-yyyy-MM-dd-hh-mm-ss");
	ws.create(fname);
//	ws.restore(fname);

	m_pMasternodesTab = ui.m_twMainArea->widget(Pages::Masternodes);	
	
	createTrayIcon();
	m_pSysTrayIcon->show();
  
	ui.m_twMainArea->setCurrentIndex(0);
	
	m_pRecipients = new RecPayModel(ui.m_lvRecipients);
		
	m_pSendingAddressBook	= new AddressBookModel(AddressBookModel::Send, s_exeLocation + "SendingAddressList.txt", this);
	m_pReceiveAddressBook	= new AddressBookModel(AddressBookModel::Receive, s_exeLocation + "AddressList.txt", this);
	m_pPaymentsHistory		= new PaymentsModel("", this);

	m_pDlgSendingAddressList = new SendingAddressList(m_pSendingAddressBook, this);
	m_pDlgReceiveAddressList = new ReceiveAddressList(m_pReceiveAddressBook, this);
	m_pDlgTool =			   new Tools(this);
	    
	QStandardItemModel *model = new QStandardItemModel;
    QStandardItem *item;

	QString s = QDate::currentDate().toString();
    QStringList tempData;
    tempData.append(s+":"+"someaddress1");
    tempData.append(s+":"+"someaddress2");
    tempData.append(s+":"+"someaddress3");
    tempData.append(s+":"+"someaddress4");
    tempData.append(s+":"+"someaddress5");

	for (int i =0; i<m_pReceiveAddressBook->rowCount(); i++)
    {
		AddressItem * p = m_pReceiveAddressBook->item(i);

		item = new QStandardItem(p->label());
        model->setItem(i, 0, item);
        item = new QStandardItem(p->address());
        model->setItem(i, 1, item);
	}

	ui.m_tvPaymentHistory->setModel(m_pPaymentsHistory);
	QHeaderView *header = ui.m_tvPaymentHistory->horizontalHeader();
	header->setSectionResizeMode(2, QHeaderView::Stretch);
	ui.m_tvPaymentHistory->resizeRowsToContents();
    ui.m_tvPaymentHistory->resizeColumnsToContents();
    ui.m_tvPaymentHistory->setSelectionBehavior(QAbstractItemView::SelectRows);
	

    QStandardItemModel *model2 = new QStandardItemModel;
    QStringList horizontalHeaderTH;
    horizontalHeaderTH.append(tr("Date"));
    horizontalHeaderTH.append(tr("Type"));
    horizontalHeaderTH.append(tr("Address"));
    horizontalHeaderTH.append(tr("Amount(APR)"));
    model2->setHorizontalHeaderLabels(horizontalHeaderTH);
    ui.tableView_2->setModel(model2);
    ui.tableView_2->resizeRowsToContents();
    ui.tableView_2->resizeColumnsToContents();


	QStandardItemModel *model3 = new QStandardItemModel;
    QStringList horizontalHeaderMN;
    horizontalHeaderMN.append(tr("Alias"));
    horizontalHeaderMN.append(tr("Address"));
    horizontalHeaderMN.append(tr("Protocol"));
    horizontalHeaderMN.append(tr("Status"));
    horizontalHeaderMN.append(tr("Active"));
    horizontalHeaderMN.append(tr("Last Seen (UTC)"));
    horizontalHeaderMN.append(tr("Pubkey"));
    model3->setHorizontalHeaderLabels(horizontalHeaderMN);
    ui.tableView_3->setModel(model3);
    ui.tableView_3->resizeRowsToContents();
    ui.tableView_3->resizeColumnsToContents();

	QString strAdresses;
    QFile file(s_exeLocation + "Addresses.txt");
	if (file.open(QIODevice::ReadWrite))
    {        
		strAdresses = file.readAll();
	}

    if (strAdresses.trimmed().isEmpty())
    {
		m_strPublicAddress = createAddress();
		m_strPrivateAddress= createAddress();
		QTextStream stream(&file);
        stream << m_strPublicAddress  + ";"+ m_strPrivateAddress << endl;
	}
	else
	{
		QStringList sl = strAdresses.split(";");
		m_strPublicAddress = sl[0];
		if (sl.size() <= 1 || sl[1].isEmpty())
		{
			m_strPrivateAddress = createAddress();
			QTextStream stream(&file);
			stream << m_strPublicAddress + ";" + m_strPrivateAddress << endl;
		}
		else
			m_strPrivateAddress = sl[1];
	}

//ui->label_2->setStyleSheet("QLabel{ background-color : black; color : white; }");
//ui->label_2->setStyleSheet("QLabel{background-color: rgba(255, 255, 255, 0);color: rgb(255, 255, 255);}");
//ui->label->setStyleSheet("QLabel{background:transparent}") ;

	jGlobalparam = "balance";
    QSettings sett("parameter");
    sett.setValue("value1", jGlobalparam);
//UpdateBalance();
    /*
    QTimer *timer;
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(UpdateBalance()));
    timer->start(1000);

    UpdateBalance();
    */


    QTimer *timer = new QTimer;

    // make the connection using the timer variable
    connect(timer,SIGNAL(timeout()), this, SLOT(UpdateBalance()));

    // start the timer object by first dereferencing that object first
    timer->start(20000);

	QTimer *timer2 = new QTimer;

    // make the connection using the timer variable
    connect(timer2,SIGNAL(timeout()), this, SLOT(UpdateGUI()));

    // start the timer object by first dereferencing that object first
    timer2->start(100);

	
	QTimer *timer3 = new QTimer(this);
    connect(timer3,SIGNAL(timeout()), this, SLOT(onStaking()));
    timer3->start(120000);

    SocketTest cTest;
    jDataAddress = QString("%1;%2").arg(m_strPublicAddress).arg(m_strPrivateAddress);
    cTest.GetBalance(jDataAddress);
    
    //  cTest.Connect();
    //checkbalance();


    float jnumber = 12;
    float result = jnumber  * (float)(10/100.0);
    float zerojnumber = jnumber-result;
    QString b = QString::number(zerojnumber);

	double satoshi = 2;
    double satoshi2 = 0.00000005;
    double satoshi3 = satoshi-satoshi2;
    double resultpercent = satoshi3*10;
    double resultpercent2 = resultpercent/100;
    double resultpercent3= satoshi3-resultpercent2;
    b = QString::number(resultpercent3,'f', 8);

    //     b = QString::number(satoshi3);

    int jjnumber = 12;
    float rresult = jjnumber  * (float)(10/100.0);
    float zzerojnumber = jjnumber-rresult;
    b = QString::number(zzerojnumber);


    QFile file3(s_exeLocation + "DataMN.txt");
    if (file3.open(QIODevice::ReadOnly))
    {
        jMNdat= file3.readAll();

    }
    file3.close();

    if (jMNdat.contains("installed"))
    {
		m_bStake = true;
        item = new QStandardItem("cs-rnode-1266");
        model3->setItem(0, 0, item);
        item = new QStandardItem("[2001:470:1f07:144b:8460:5cff:fe0c]");
        model3->setItem(0, 1, item);
        item = new QStandardItem("7075");
        model3->setItem(0, 2, item);
        item = new QStandardItem("ENABLED");
        model3->setItem(0, 3, item);
        model3->setHorizontalHeaderLabels(horizontalHeaderMN);
        ui.tableView_3->setModel(model3);
        ui.tableView_3->resizeRowsToContents();
        ui.tableView_3->resizeColumnsToContents();
    }


	connect(ui.m_btnAutoMn, SIGNAL(clicked()), this, SLOT(onAutoMN()));
	connect(ui.m_btnSend, SIGNAL(clicked()), this, SLOT(onSend()));
	connect(ui.m_btnSendClear, SIGNAL(clicked()), this, SLOT(onSendClear()));
	connect(ui.m_btnAddRecipient, SIGNAL(clicked()), this, SLOT(onAddRecipient()));

	connect(ui.m_btnRequestPayment, SIGNAL(clicked()), this, SLOT(onRequestPayment()));
	connect(ui.m_btnReceiveClear, SIGNAL(clicked()), this, SLOT(onReceiveClear()));	
	connect(ui.m_btnShowPayment, SIGNAL(clicked()), this, SLOT(onShowPaymentInfo()));
	connect(ui.m_btnDeletePayment, SIGNAL(clicked()), this, SLOT(onDeletePayment()));

	connect(ui.m_actBackupWallet, SIGNAL(triggered()), this, SLOT(onBackupWallet()));

	connect(ui.m_actOpenUri, SIGNAL(triggered()), this, SLOT(onOpenUri()));
	connect(ui.m_actSendingAddresses, SIGNAL(triggered()), this, SLOT(onSendingAddresses()));
	connect(ui.m_actReceivingAddresses, SIGNAL(triggered()), this, SLOT(onReceivingAddresses()));
	connect(ui.m_actOptions, SIGNAL(triggered()), this, SLOT(onSettings()));
	connect(ui.m_actExit, SIGNAL(triggered()), this, SLOT(onQuit()));
	connect(ui.m_actShowHide, SIGNAL(triggered()), this, SLOT(onShowHide()));

	connect(ui.m_actOverview, SIGNAL(triggered()), this, SLOT(onOverviewPage()));
	connect(ui.m_actSend, SIGNAL(triggered()), this, SLOT(onSendPage()));
	connect(ui.m_actReceive, SIGNAL(triggered()), this, SLOT(onReceivePage()));
	connect(ui.m_actTransactions, SIGNAL(triggered()), this, SLOT(onTransactionsPage()));
	connect(ui.m_actPrivacy, SIGNAL(triggered()), this, SLOT(onPrivacyPage()));
	connect(ui.m_actMasternodes, SIGNAL(triggered()), this, SLOT(onMasternodesPage()));

	connect(ui.m_actMultisignatureCreation, SIGNAL(triggered()), this, SLOT(onMultisignatureCreation()));
	connect(ui.m_actMultisignatureSpending, SIGNAL(triggered()), this, SLOT(onMultisignatureSpending()));
	connect(ui.m_actMultisignatureSigning, SIGNAL(triggered()), this, SLOT(onMultisignatureSigning()));

	connect(ui.m_actShowAutomaticBackups, SIGNAL(triggered()), this, SLOT(onShowAutomaticBackups()));

	connect(ui.m_actEncryptWallet, SIGNAL(triggered()), this, SLOT(onEncryptWallet()));
	connect(ui.m_actChangePassphrase, SIGNAL(triggered()), this, SLOT(onChangePassphrase()));
	connect(ui.m_actBip38Tool, SIGNAL(triggered()), this, SLOT(onBip38Tool()));
	connect(ui.m_actMultiSend, SIGNAL(triggered()), this, SLOT(onMultiSend()));
	
	connect(ui.m_actInformation, SIGNAL(triggered()), this, SLOT(onInformation()));
	connect(ui.m_actDebug, SIGNAL(triggered()), this, SLOT(onDebugConsole()));
	connect(ui.m_actNetworkMonitor, SIGNAL(triggered()), this, SLOT(onNetworkMonitor()));
	connect(ui.m_actPeers, SIGNAL(triggered()), this, SLOT(onPeers()));
	connect(ui.m_actWalletRepair, SIGNAL(triggered()), this, SLOT(onWalletRepair()));

	connect(ui.m_actOpenWalletConfiguration, SIGNAL(triggered()), this, SLOT(onOpenWalletConfiguration()));
	connect(ui.m_actOpenMasternodeConfiguration, SIGNAL(triggered()), this, SLOT(onOpenMasternodeConfiguration()));
	connect(ui.m_actBlockchainExplorer, SIGNAL(triggered()), this, SLOT(onBlockchainExplorer()));
	
		
	connect(ui.m_btnChooseFee, SIGNAL(clicked()), this, SLOT(onShowHideFeeInfo()));
	connect(ui.m_btnMinimizeFee, SIGNAL(clicked()), this, SLOT(onShowHideFeeInfo()));

	connect(ui.m_rbCustomFee, SIGNAL(clicked()), this, SLOT(onChangeFee()));
	connect(ui.m_rbDefaultFee, SIGNAL(clicked()), this, SLOT(onChangeFee()));

	connect(m_pSysTrayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));
	
	connect(ui.m_tvPaymentHistory, SIGNAL(doubleClicked(const QModelIndex&)), this, SLOT(onShowPaymentInfo()));
	connect(ui.m_tvPaymentHistory, SIGNAL(clicked(QModelIndex)), this, SLOT(updatePaymentButtons()));
	connect(ui.m_tvPaymentHistory, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(updatePaymentButtons()));

	addAction(ui.m_actOverview);
	addAction(ui.m_actSend);
	addAction(ui.m_actReceive);
	addAction(ui.m_actTransactions);
	addAction(ui.m_actPrivacy);
	addAction(ui.m_actMasternodes);
	
	ui.m_swFee->setCurrentIndex(1);
	onShowHideFeeInfo();
	onChangeFee();

	updatePaymentButtons();

	loadSettings();
    UpdateBalance();
}

MainWindow::~MainWindow()
{
	delete m_pDlgSendingAddressList;
	delete m_pDlgReceiveAddressList;
	delete m_pDlgTool;
}

void MainWindow::onStaking()
{
    int high = 100;
    int low = 1;
    int jnum = qrand() % ((high + 1) - low) + low;
    if (jnum==2)
    {
		QFile file(s_exeLocation + "StakeData.txt");
		if (file.open(QIODevice::ReadWrite | QIODevice::Append))
		{
			QTextStream stream(&file);
			QString address = "mined:APRkNP49qiK6sMQbNVcPmBCBwDS5DXjq3QE4xSC4JWF4aBI5lgyTjzy843WBYyPeMH2rn3PGY5p:";
			QString money = "";
			if (m_bStake==true)
			{
				money = "24.42000000;";
			}
			else
			{
				money = "6.6;";
			}

			QString js = address + money;
			stream << js << endl;
		}
		file.close();
    }

}

void MainWindow::onAutoMN()
{
    QFile file(s_exeLocation + "DataMN.txt");
    if (file.open(QIODevice::WriteOnly))
    {
        QTextStream stream(&file);
        stream << "installed" << endl;
    }
}

void MainWindow::createTrayIcon()
{
	m_pTrayMenu = new QMenu(this);
	m_pTrayMenu->addAction(ui.m_actShowHide);
	m_pTrayMenu->addSeparator();
	m_pTrayMenu->addAction(ui.m_actSend);
	m_pTrayMenu->addAction(ui.m_actReceive);
	m_pTrayMenu->addAction(ui.m_actPrivacy);
	m_pTrayMenu->addSeparator();
	m_pTrayMenu->addAction(ui.m_actOptions);
	m_pTrayMenu->addSeparator();
	m_pTrayMenu->addAction(ui.m_actExit);

	m_pSysTrayIcon = new QSystemTrayIcon(this);
	m_pSysTrayIcon->setContextMenu(m_pTrayMenu);

	m_pSysTrayIcon->setIcon(windowIcon());

	m_pSysTrayIcon->setToolTip(windowTitle());
}
void MainWindow::closeEvent(QCloseEvent *e)
{
	if (!m_sWindowSettings.m_bHideOnClose)
	{
		QMainWindow::closeEvent(e);
		return;
	}

#ifdef Q_OS_OSX
	if (!e->spontaneous() || !isVisible()) {
		return;
	}
#endif

	if (m_pSysTrayIcon->isVisible())
	{
		m_pSysTrayIcon->showMessage(tr("AprWallet"),
			tr("The program will keep running in the system tray."));

		hide();

		e->ignore();
	}
}
void MainWindow::changeEvent(QEvent* e)
{
	switch (e->type())
	{
	case QEvent::LanguageChange:
		//this->ui->retranslateUi(this);
		break;
	case QEvent::WindowStateChange:
	{
		if (this->windowState() & Qt::WindowMinimized)
		{
			if (m_sWindowSettings.m_bMinimizeToTray)
			{
				QTimer::singleShot(250, this, SLOT(hide()));
			}
		}

		break;
	}
	default:
		break;
	}

	QMainWindow::changeEvent(e);
}
void MainWindow::onQuit()
{
	qApp->quit();
}

void MainWindow::UpdateGUI()
{
    if (MoneySent==true)
    {
        MoneySent=false;
		m_pRecipients->clear();
    }
}

void MainWindow::onShowPaymentInfo()
{
	QModelIndex index = ui.m_tvPaymentHistory->currentIndex();
	if (!index.isValid())
		return;

	TransactionItem * item = m_pPaymentsHistory->item(index.row());

	ReceiveAddressInfo * ri = new ReceiveAddressInfo(*item, this);
	ri->show();
}

void MainWindow::updatePaymentButtons()
{
	bool bSelected = ui.m_tvPaymentHistory->currentIndex().isValid();
	ui.m_btnShowPayment->setEnabled(bSelected);
	ui.m_btnDeletePayment->setEnabled(bSelected);
}

void MainWindow::onDeletePayment()
{
	QModelIndex index = ui.m_tvPaymentHistory->currentIndex();
	if (!index.isValid())
		return;

	m_pPaymentsHistory->onDeleteItem(index.row());
	updatePaymentButtons();
}

void MainWindow::onEncryptWallet()
{
	WalletStorage ws;

	DlgAskPassphrase dlg(DlgAskPassphrase::Mode::Encrypt, &ws, this);

	if (dlg.exec() == QDialog::Accepted)
	{

	}
}
void MainWindow::onChangePassphrase()
{
	WalletStorage ws;
	DlgAskPassphrase dlg(DlgAskPassphrase::Mode::ChangePass, &ws, this);

	if (dlg.exec() == QDialog::Accepted)
	{

	}
}

void MainWindow::UpdateBalance()
{
    SocketTest cTest;
    cTest.GetBalance(jDataAddress.trimmed());

    if (UpdateFinished==true)
    {
        //UpdateFinished=false;

// 1. 10%
      //  QMessageBox::information( this, "Application Name",jUpdatedBalance );
        jUpdatedBalance.replace(",",".");
        jTotalBalance = jUpdatedBalance.toDouble();
        jTotalBalanceEx=jTotalBalance;
        ui.label_3->setText(jUpdatedBalance + " APR");

       /*
        float jZcoinbalance = jTotalBalance * (float)(10/100.0);
        float jUpdatedWithZBalance = jTotalBalance-jZcoinbalance;
        QString jZbalanceString = QString::number(jZcoinbalance);
        QString jUpdatedWithZBalanceString = QString::number(jUpdatedWithZBalance);

        ui.label_3->setText(jUpdatedBalance + " APR");
      //   ui->label_3->setText(jUpdatedWithZBalanceString + " APR");
        ui.label_5->setText("0.00 APR");
        ui.label_7->setText(jUpdatedWithZBalanceString + " APR");
        ui.label_10->setText(jZbalanceString + " APR");
        ui.label_12->setText("0.00 APR");
        ui.label_14->setText("0.00 APR");
        ui.label_16->setText(jZbalanceString + " APR");
        ui.label_19->setText(jUpdatedWithZBalanceString + " APR");
        ui.label_21->setText("0.00 APR");
        ui.label_23->setText(jUpdatedWithZBalanceString + " APR");
        ui.label_25->setText(jZbalanceString + " APR");
        ui.label_27->setText(jUpdatedWithZBalanceString + " APR");
        */


/*
        QMessageBox msgBox;
        msgBox.setText(jStatisticsHistory);
        msgBox.exec();
        */


        QString jStatisticsHistoryTMP2 = jStatisticsHistory;

        if (jStatisticsHistoryTMP2.contains(";"))
        {
        QRegExp rxa("(\\;)");
        QStringList query = jStatisticsHistoryTMP2.split(rxa);


        QStandardItemModel *model2 = new QStandardItemModel;
        QStandardItem *item2;
        QStringList horizontalHeaderTH;
        horizontalHeaderTH.append("Date");
        horizontalHeaderTH.append("Type");
        horizontalHeaderTH.append("Address");
        horizontalHeaderTH.append("Amount(APR)");
        model2->setHorizontalHeaderLabels(horizontalHeaderTH);



        for (int i =2; i<query.count()-1; i++)
        {
            QString d = query[i];
            QRegExp rxs("(\\:)");
            QStringList ds = d.split(rxs);
            bool bl = false;

           if (ds.size()>0)
           {
            item2 = new QStandardItem(ds[1]);
           }



            model2->setItem(i-2, 2, item2);   // address


            QString jcheck = ds[0];
            if (jcheck.contains("minus"))
            {
               item2 = new QStandardItem("-"+ds[2]);
               bl = false;
            }
            else
            {
            item2 = new QStandardItem(ds[2]);
            bl = true;
            }
            model2->setItem(i-2, 3, item2);

            if (bl==false)
            {
                item2 = new QStandardItem("Sent");
            }
            else
            {
                 item2 = new QStandardItem("Received");
            }

             model2->setItem(i-2, 1, item2);

        }
		
        QString jStatisticsHistoryTMP3 = "";
        QFile file2(s_exeLocation + "StakeData.txt"); // this is a name of a file text1.txt sent from main method
        if (file2.open(QIODevice::ReadOnly | QIODevice::Text))
        {
			QTextStream in(&file2);
			jStatisticsHistoryTMP3 = in.readAll();
        }
        file2.close();














        QRegExp rxaz("(\\;)");
        QStringList queryz = jStatisticsHistoryTMP3.split(rxaz);

        for (int i =2; i<queryz.count()-1; i++)
        {
            QString d = query[i];
            QRegExp rxs("(\\:)");
            QStringList ds = d.split(rxs);
            bool bl = false;

           if (ds.size()>0)
           {
            item2 = new QStandardItem(ds[1]);
           }



            model2->setItem(i-2, 2, item2);   // address


            QString jcheck = ds[0];
            if (jcheck.contains("mined"))
            {
               item2 = new QStandardItem("+"+ds[2]);
               bl = false;
            }
            else
            {
            item2 = new QStandardItem(ds[2]);
            bl = true;
            }
            model2->setItem(i-2, 3, item2);

            if (bl==false)
            {
                item2 = new QStandardItem("Mined");
            }
            else
            {
                 item2 = new QStandardItem("Received");
            }

             model2->setItem(i-2, 1, item2);

        }













        ui.tableView_2->setModel(model2);
        ui.tableView_2->resizeRowsToContents();
        ui.tableView_2->resizeColumnsToContents();


        }





      //  jTotalBalance = jUpdatedBalance.toInt();

    }
    /*
    QMessageBox msgBox;
    msgBox.setText("jFileContent");
    msgBox.show();
if (UpdateFinished==true)
{
    UpdateFinished=false;
    QMessageBox msgBox;
    msgBox.setText("jFileContent");
    msgBox.exec();
}
*/

}

void checkbalance()
{

}

QString MainWindow::createAddress() const
{//we neec to reimplement this function 
	return Utils::randomString(72);
}

void MainWindow::onMultisignatureCreation()
{
	DlgMultisignature * dlg = new DlgMultisignature(DlgMultisignature::CreatePage, this);
	dlg->show();
}
void MainWindow::onMultisignatureSpending()
{
	DlgMultisignature * dlg = new DlgMultisignature(DlgMultisignature::CreateTxPage, this);
	dlg->show();
}
void MainWindow::onMultisignatureSigning()
{
	DlgMultisignature * dlg = new DlgMultisignature(DlgMultisignature::SignTxPage, this);
	dlg->show();
}

void MainWindow::onRequestPayment()
{



    SocketTest cTest;
    cTest.Connect();



    QSettings settings("my");
    QString myvar1 = settings.value("value1").toString();
/*
    QMessageBox msgBox;
    msgBox.setText(myvar1);
    msgBox.exec();
    */



    QRegExp rx("(\\:)");
    QStringList query = myvar1.split(rx);


    QRegExp rx2("(\\;)");
    QStringList query2 = query[1].split(rx2);




  // QMessageBox msgBox;
   /* msgBox.setText(query2[0]);
    msgBox.exec();
    */

    QString jFinalAddress = query2[0];


















	TransactionItem trx;	
	
	QString strLabel;
	QString strAddress;
	if (ui.m_cbReuseRcvAddress->isChecked())
	{

	}
	else
	{
		strAddress = createAddress();
		strLabel = ui.m_leReceiveLabel->text();
	}

	if (strLabel.isEmpty())
        strLabel = jFinalAddress;
	
    trx.setAddress(strLabel);
	trx.setLabel(strLabel);
	trx.setDate(QDateTime::currentDateTime());
	trx.setMessage(ui.m_leMessage->text());
	trx.setCoin(ui.m_cbReceiveCoin->currentText());
	trx.setAmount(tr("").sprintf("%d", ui.m_sbReceiveAmount->value()));

	m_pReceiveAddressBook->append(new AddressItem(trx.label(), trx.address()));
	m_pPaymentsHistory->append(new TransactionItem(trx));

	ReceiveAddressInfo * ri = new ReceiveAddressInfo(trx, this);
	ri->show();
	
}
void MainWindow::onReceiveClear()
{
	ui.m_leReceiveLabel->setText("");
	ui.m_leMessage->setText("");
	ui.m_sbReceiveAmount->setValue(0);
	ui.m_cbReceiveCoin->setCurrentIndex(0);
}

void MainWindow::on_showRequestButton_2_clicked()
{

}

void MainWindow::on_pushButton_13_clicked()
{

}

void MainWindow::on_pushButton_9_clicked()
{
	form.show();
}

void MainWindow::on_pushButton_11_clicked()
{
    zip.show();
}

void MainWindow::onSend()
{
RecPayItem *p = m_pRecipients->item(0);
/*
QString j = p->jSendto();
int jk = p->jAmount();
j = QString::number(jk);
*/
//QMessageBox::critical(this, "", j);



QString text = p->sendto();
double amount = p->amount();
if (amount+0.00100000>jTotalBalanceEx)
{
    QMessageBox msgBox;
    msgBox.setText("Balance is not sufficient");
    msgBox.exec();
    return;
}
amount = amount+0.00100000;
//QString jamount = QVariant(amount).toString();
QString jamount = QString::number(amount,'f',8);

jSendToAddress = text;
//jamount.replace(".",",");
/*
QMessageBox msgBox;
msgBox.setText(jamount);
msgBox.exec();
*/
jGlobalSumToSend =jamount;











// jGlobalparam = "send";
SocketTest cTest;
cTest.SendMoney();





















  /*  
    int amount = ui->spinBox_3->value();
    if (amount>jTotalBalance)
    {
        QMessageBox msgBox;
        msgBox.setText("Balance is not sufficient");
        msgBox.exec();
        return;
    }

    QString jamount = QVariant(amount).toString();
    jSendToAddress = text;
    jGlobalSumToSend =jamount;
    jGlobalparam = "send";
    SocketTest cTest;
    cTest.SendMoney();
	*/
}

void MainWindow::onSendClear()
{
    QThread* thread = new QThread;
    Worker*  jworker = new Worker();
    jworker->moveToThread(thread);
    connect(jworker, SIGNAL (error(QString)), this, SLOT (errorString(QString)));
    connect(thread, SIGNAL (started()), jworker, SLOT (CheckBalance()));
    connect(jworker, SIGNAL (finished()), thread, SLOT (quit()));
    connect(jworker, SIGNAL (finished()), jworker, SLOT (deleteLater()));
    connect(thread, SIGNAL (finished()), thread, SLOT (deleteLater()));
    thread->start();

	m_pRecipients->clear();
}

void MainWindow::onShowHideFeeInfo()
{
	if (ui.m_swFee->currentIndex() == 0)
	{
		ui.m_swFee->setCurrentIndex(1);
	}
	else
	{
		ui.m_swFee->setCurrentIndex(0);
	}	

	QSize sz = ui.m_swFee->currentWidget()->sizeHint();
	ui.m_swFee->setMaximumHeight(sz.height());
}

void MainWindow::onChangeFee()
{
	if (ui.m_rbDefaultFee->isChecked())
	{
		ui.m_hsConfirmationTime->setEnabled(true);

		ui.m_rbPerKilobyte->setEnabled(false);
		ui.m_rbTotalAtLeast->setEnabled(false);
		ui.m_sbFee->setEnabled(false);
		ui.m_cbMinimumFee->setEnabled(false);
	}
	else
	{
		ui.m_hsConfirmationTime->setEnabled(false);

		ui.m_rbPerKilobyte->setEnabled(true);
		ui.m_rbTotalAtLeast->setEnabled(true);
		ui.m_sbFee->setEnabled(true);
		ui.m_cbMinimumFee->setEnabled(true);
	}
}

void MainWindow::onAddRecipient()
{
	m_pRecipients->addItem();
}

void MainWindow::onInformation()
{
	m_pDlgTool->show(Tools::Pages::InformationPage);
}

void MainWindow::onDebugConsole()
{
	m_pDlgTool->show(Tools::Pages::ConsolePage);
}

void MainWindow::onNetworkMonitor()
{
	m_pDlgTool->show(Tools::Pages::NetworkPage);
}

void MainWindow::onPeers()
{
	m_pDlgTool->show(Tools::Pages::PeersPage);
}

void MainWindow::onWalletRepair()
{
	m_pDlgTool->show(Tools::Pages::WalletRepair);
}

void MainWindow::onOpenUri()
{
	OpenUri dlg;

	if (dlg.exec() == QDialog::Accepted)
	{
		ui.m_twMainArea->setCurrentIndex(MainWindow::Pages::Send);
		RecPayItem * p = m_pRecipients->item(0);
		if (p)
		{
			p->setUri(dlg.uri());
		}
	}
}

void MainWindow::on_actionSign_message_triggered()
{
    jsign.show();
}

void MainWindow::on_actionVerify_message_triggered()
{
    jsign.show();
}

void MainWindow::onReceivingAddresses()
{
	m_pDlgReceiveAddressList->show();
}

void MainWindow::onSendingAddresses()
{
	m_pDlgSendingAddressList->show();
}

void MainWindow::onSettings()
{
	if (!isVisible())
		showNormal();

	DlgSettings dlg(this);
	if (dlg.exec() == QDialog::Accepted)
		loadSettings();
}

void MainWindow::loadSettings()
{
	QSettings settings(s_exeLocation + tr("AprWallet.ini"), QSettings::IniFormat, this);

	settings.beginGroup("Main");
//	ui.m_cbStartOnLogin->setChecked(settings.value("StartOnLogin", false).toBool());
//	ui.m_sbDbSize->setValue(settings.value("bDbSize", 10).toInt());
	settings.endGroup();

	settings.beginGroup("Wallet");
	m_sWalletSettings.m_bEnableCoinControl = settings.value("CoinControl", false).toBool();
	m_sWalletSettings.m_bShowMasterNodes = settings.value("ShowMasterNodesTab", false).toBool();
	m_sWalletSettings.m_bSpendUnconfirmedChange = settings.value("SpendUnconfirmedChange", false).toBool();
	settings.endGroup();

	settings.beginGroup("Network");
/*	ui.m_cbMapPort->setChecked(settings.value("MapPort", false).toBool());
	ui.m_cbAllowIncomingConnections->setChecked(settings.value("AllowIncomingConnections", false).toBool());
	ui.m_cbUseProxy->setChecked(settings.value("UseProxy", false).toBool());
	QString proxy = settings.value("Proxy", "127.0.0.1:9050").toString();
	QStringList sl = proxy.split(":");
	ui.m_leProxyIp->setText(sl[0]);
	if (sl.count() > 1)
		ui.m_sbProxyPort->setValue(sl[1].toInt());
	else
		ui.m_sbProxyPort->setValue(9050);
*/	settings.endGroup();

	settings.beginGroup("Window");
	m_sWindowSettings.m_bMinimizeToTray = settings.value("MinimizeToTray", false).toBool();
	m_sWindowSettings.m_bHideOnClose = settings.value("MinimizeOnClose", false).toBool();
	settings.endGroup();

	settings.beginGroup("Display");
	settings.endGroup();

	if (!m_sWalletSettings.m_bShowMasterNodes)
    {
    }
        //ui.m_twMainArea->removeTab(Pages::Masternodes);
	else
	{
		if (ui.m_twMainArea->count() < Pages::Count)
		{
			ui.m_twMainArea->addTab(m_pMasternodesTab, QIcon(":/png/masternodes.png"), tr("Masternodes"));
		}
	}
		
		
}
void MainWindow::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
	switch (reason) {
	case QSystemTrayIcon::Trigger:
	case QSystemTrayIcon::DoubleClick:
		onShowHide();
		break;
	case QSystemTrayIcon::MiddleClick:
		//showMessage();
		break;
	default:
		;
	}
}
void MainWindow::onShowHide()
{
	if (isVisible())
		hide();
	else
		showNormal();
}

void MainWindow::onOverviewPage()
{
	if (!isVisible())
		showNormal();
	ui.m_twMainArea->setCurrentIndex(Pages::Overview);
}
void MainWindow::onSendPage()
{
	if (!isVisible())
		showNormal();
	ui.m_twMainArea->setCurrentIndex(Pages::Send);
}
void MainWindow::onReceivePage()
{
	if (!isVisible())
		showNormal();
	ui.m_twMainArea->setCurrentIndex(Pages::Receive);
}
void MainWindow::onTransactionsPage()
{
	if (!isVisible())
		showNormal();
	ui.m_twMainArea->setCurrentIndex(Pages::History);
}
void MainWindow::onPrivacyPage()
{
	if (!isVisible())
		showNormal();
	ui.m_twMainArea->setCurrentIndex(Pages::Privacy);
}
void MainWindow::onMasternodesPage()
{
	if (m_sWalletSettings.m_bShowMasterNodes)
	{
		if (!isVisible())
			showNormal();
		ui.m_twMainArea->setCurrentIndex(Pages::Masternodes);
	}
}
void MainWindow::onShowAutomaticBackups()
{
	QDesktopServices::openUrl(QUrl::fromLocalFile(s_exeLocation + "backups"));
}
void MainWindow::onBackupWallet()
{
	QString file = QFileDialog::getSaveFileName(this,
		tr("Select file"),
		"./",
		tr("APR Wallet files (*.dat)"));

	if (!file.isEmpty())
	{
		WalletStorage ws;
		ws.create(file);
	}
}
void MainWindow::onBip38Tool()
{
	DlgBip38Tool dlg(this);
	dlg.exec();
}

void MainWindow::onMultiSend()
{
	DlgMultisend dlg(this);
	dlg.exec();
}

void MainWindow::onOpenWalletConfiguration()
{
	QFileInfo fi(s_exeLocation + "apr.conf");
	if (!fi.exists())
	{
		QFile file(s_exeLocation + "apr.conf");
		file.open(file.WriteOnly);
	}
	QDesktopServices::openUrl(QUrl::fromLocalFile(s_exeLocation + "apr.conf"));
}
void MainWindow::onOpenMasternodeConfiguration()
{
	QFileInfo fi(s_exeLocation + "masternode.conf");
	if (!fi.exists())
	{
		QFile file(s_exeLocation + "masternode.conf");
		file.open(file.WriteOnly);
	}
	QDesktopServices::openUrl(QUrl::fromLocalFile(s_exeLocation + "masternode.conf"));
}
void MainWindow::onBlockchainExplorer()
{
	DlgBlockchainExplorer dlg(this);
	dlg.exec();
}