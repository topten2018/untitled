#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QTabWidget>
#include <QTabBar>
#include <QRegExp>
#include <QObject>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QDebug>
#include <QHBoxLayout>
#include "dialog.h"
#include <QDialog>
#include <QString>
#include "sockettest.h"
#include <QSettings>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QStringList>
#include <QDate>
#include <QFile>
#include <QTextStream>
#include <QTimer>
#include <QThread>
#include "worker.h"
#include <cmath>
#include <QDebug>

#include "Models/RecPayModel.h"

int jTotalBalance=0;
QStringList jReceiveAddresses;
QStringList jSendingAddressListOUT;
QString jGlobalparam = "";
QString jAddressParam="";

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("APR Wallet Version 1.0"));
	this->setWindowIcon(*(new QIcon(":/ico/icon.ico")));
  
	ui->tabWidget->setTabIcon(0, QIcon(":/png/overview.png"));
	ui->tabWidget->setTabIcon(1, QIcon(":/png/send.png"));
    ui->tabWidget->setTabIcon(2, QIcon(":/png/receive.png"));
    ui->tabWidget->setTabIcon(3, QIcon(":/png/history.png"));
    ui->tabWidget->setTabIcon(4, QIcon(":/png/privacy.png"));
    ui->tabWidget->setTabIcon(5, QIcon(":/png/masternodes.png"));
	
	m_pRecipients = new RecPayModel(ui->m_lvRecipients);
		
    QString fileName = "AddressList.txt";
    QFile inputFile(fileName);
    if (inputFile.open(QIODevice::ReadOnly))
    {
		QTextStream in(&inputFile);
        while (!in.atEnd())
        {
			QString line = in.readLine();
            jReceiveAddresses.append(line);
        }
        inputFile.close();
	}

    QString fileName2 = "SendingAddressList.txt";
    QFile inputFile2(fileName2);
    if (inputFile2.open(QIODevice::ReadOnly))
    {
		QTextStream in(&inputFile2);
        while (!in.atEnd())
        {
			QString line = in.readLine();
            jSendingAddressListOUT.append(line);
		}
        inputFile2.close();
	}

	jSendingAddressesOUTList = jSendingAddressListOUT.join(";");
/*
QMessageBox msgBox;
msgBox.setText(jSendingAddressesOUTList);
msgBox.exec();
*/
	QStandardItemModel *model = new QStandardItemModel;
    QStandardItem *item;

    //Заголовки столбцов
    QStringList horizontalHeader;
    horizontalHeader.append(tr("Date"));
    horizontalHeader.append(tr("Label"));
    horizontalHeader.append(tr("Message"));
    horizontalHeader.append(tr("Amount(APR)"));

	QString s = QDate::currentDate().toString();
    QStringList tempData;
    tempData.append(s+":"+"someaddress1");
    tempData.append(s+":"+"someaddress2");
    tempData.append(s+":"+"someaddress3");
    tempData.append(s+":"+"someaddress4");
    tempData.append(s+":"+"someaddress5");

               /*
               for (int i =0; i<5; i++)
               {
                   QString d = tempData[i];
                   item = new QStandardItem(d);
                    model->setItem(i, 1, item);

               }
               */


	for (int i =0; i<jReceiveAddresses.count(); i++)
    {
		QString d = jReceiveAddresses[i];
        QRegExp rxs("(\\:)");
        QStringList ds = d.split(rxs);

		item = new QStandardItem(ds[0]);
        model->setItem(i, 0, item);
        item = new QStandardItem(ds[1]);
        model->setItem(i, 1, item);
	}

	model->setHorizontalHeaderLabels(horizontalHeader);
    ui->tableView->setModel(model);
    ui->tableView->resizeRowsToContents();
    ui->tableView->resizeColumnsToContents();
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    connect(ui->tableView, SIGNAL(clicked(const QModelIndex&)), this, SLOT(onTableClicked()));


    QStandardItemModel *model2 = new QStandardItemModel;
    QStringList horizontalHeaderTH;
    horizontalHeaderTH.append(tr("Date"));
    horizontalHeaderTH.append(tr("Type"));
    horizontalHeaderTH.append(tr("Address"));
    horizontalHeaderTH.append(tr("Amount(APR)"));
    model2->setHorizontalHeaderLabels(horizontalHeaderTH);
    ui->tableView_2->setModel(model2);
    ui->tableView_2->resizeRowsToContents();
    ui->tableView_2->resizeColumnsToContents();


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
    ui->tableView_3->setModel(model3);
    ui->tableView_3->resizeRowsToContents();
    ui->tableView_3->resizeColumnsToContents();

	const QString possibleCharacters("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789");
    const int randomStringLength = 72; // assuming you want random strings of 12 characters

    QString publicaddress;
    QString privateaddress;
    QDateTime cd = QDateTime::currentDateTime();
    qsrand(cd.toTime_t());
    for(int i=0; i<randomStringLength; ++i)
    {
		int index = qrand() % possibleCharacters.length();
        QChar nextChar = possibleCharacters.at(index);
        publicaddress.append(nextChar);
	}

    for(int i=0; i<randomStringLength; ++i)
    {
		int index = qrand() % possibleCharacters.length();
        QChar nextChar = possibleCharacters.at(index);
        privateaddress.append(nextChar);
	}

      /*
           QMessageBox msgBox;
           msgBox.setText(randomString);
           msgBox.exec();
           */
	QString jFileContent = "";
    QString filename = "Data4.txt";
    QFile file(filename);
	if (file.open(QIODevice::ReadWrite))
    {
        //  QTextStream stream(&file);
        //  stream << "something" << endl;

        //  QTextStream ReadFile(&file);
        /*
        while (!ReadFile.atEnd())
            {
                jFileContent = ReadFile.re.readLine();
                jAddressParam += jFileContent;


            }
            */
		jAddressParam= file.readAll();
        //   QMessageBox msgBox;
        //   msgBox.setText(jAddressParam);
        //   msgBox.exec();
		// msgBox.setText("!!!!");
        // msgBox.exec();
	}

    if (jAddressParam.trimmed().isEmpty())
    {
		QTextStream stream(&file);
        stream << publicaddress+";"+privateaddress << endl;
        jAddressParam = publicaddress+";"+privateaddress;
	}

    /*
    QMessageBox msgBox;
    msgBox.setText(jFileContent);
    msgBox.exec();
    */


//ui->label_2->setStyleSheet("QLabel{ background-color : black; color : white; }");
//ui->label_2->setStyleSheet("QLabel{background-color: rgba(255, 255, 255, 0);color: rgb(255, 255, 255);}");
//ui->label->setStyleSheet("QLabel{background:transparent}") ;

	jGlobalparam = "balance";
    QSettings sett("parameter");
    sett.setValue("value1", jGlobalparam);

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

    SocketTest cTest;
    cTest.GetBalance(jAddressParam.trimmed());
    jDataAddress = jAddressParam;
    //  cTest.Connect();
    //checkbalance();


    float jnumber = 12;
    float result = jnumber  * (float)(10/100.0);
    float zerojnumber = jnumber-result;
    QString b = QString::number(zerojnumber);

/*
             int satoshi = 2;
             int satoshitemp = 2*1000000;
              int satoshi2 = 0.00000001;
              int satoshitemp2 = satoshi2*1000000;
              // float satoshi = 1;
             // int satoshi2 = 10000000;
              int satoshi3 = satoshitemp- satoshitemp2;
              float satoshitemp3 = satoshi3/1000000;
              */


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

	connect(ui->m_btnSend, SIGNAL(clicked()), this, SLOT(onSend()));
	connect(ui->m_btnSendClear, SIGNAL(clicked()), this, SLOT(onSendClear()));
	connect(ui->m_btnAddRecipient, SIGNAL(clicked()), this, SLOT(onAddRecipient()));
/*

               QMessageBox msgBox;
               msgBox.setText(b);
               msgBox.exec();
               */
}

void MainWindow::UpdateGUI()
{
    if (MoneySent==true)
    {
        MoneySent=false;
		QMessageBox::critical(this, "", "ui->textEdit_3->clear();");
    }
}

void MainWindow::onTableClicked()
{
	QModelIndex index = ui->tableView->currentIndex();
	int i = index.row(); // now you know which record was selected
	int b = i;
	jAddressInfo= jReceiveAddresses[b];

	jReceivedAddressInfo.show();
}

void MainWindow::UpdateBalance()
{
    SocketTest cTest;
    cTest.GetBalance(jDataAddress.trimmed());

    if (UpdateFinished==true)
    {
        //UpdateFinished=false;

// 1. 10%
        jTotalBalance = jUpdatedBalance.toInt();
        float jZcoinbalance = jTotalBalance * (float)(10/100.0);
        float jUpdatedWithZBalance = jTotalBalance-jZcoinbalance;


        QString jZbalanceString = QString::number(jZcoinbalance);
         QString jUpdatedWithZBalanceString = QString::number(jUpdatedWithZBalance);

        ui->label_3->setText(jUpdatedBalance + " APR");
      //   ui->label_3->setText(jUpdatedWithZBalanceString + " APR");
        ui->label_5->setText("0.00 APR");
        ui->label_7->setText(jUpdatedWithZBalanceString + " APR");
        ui->label_10->setText(jZbalanceString + " APR");
        ui->label_12->setText("0.00 APR");
        ui->label_14->setText("0.00 APR");
        ui->label_16->setText(jZbalanceString + " APR");
        ui->label_19->setText(jUpdatedWithZBalanceString + " APR");
        ui->label_21->setText("0.00 APR");
        ui->label_23->setText(jUpdatedWithZBalanceString + " APR");
        ui->label_25->setText(jZbalanceString + " APR");
        ui->label_27->setText(jUpdatedWithZBalanceString + " APR");


/*
        QMessageBox msgBox;
        msgBox.setText(jStatisticsHistory);
        msgBox.exec();
        */

        /*
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


        ui->tableView_2->setModel(model2);
        ui->tableView_2->resizeRowsToContents();
        ui->tableView_2->resizeColumnsToContents();


        }



*/

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

MainWindow::~MainWindow()
{
    delete ui;
}

void checkbalance()
{

}


void MainWindow::on_pushButton_clicked()
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
    QStandardItemModel *model = new QStandardItemModel;
    QStandardItem *item;

	//Заголовки столбцов
	QStringList horizontalHeader;
	horizontalHeader.append(tr("Date"));
	horizontalHeader.append(tr("Label"));
	horizontalHeader.append(tr("Message"));
	horizontalHeader.append(tr("Amount(APR)"));

	QString s = QDate::currentDate().toString();


	jReceiveAddresses.append(s+":"+jFinalAddress);


    QFile fileOut("AddressList.txt");
    fileOut.open(QFile::WriteOnly|QFile::Append); // check result
    QTextStream streamOut(&fileOut);
    streamOut << s+":"+jFinalAddress << "\r\n";
    fileOut.close();

	for (int i =0; i<jReceiveAddresses.count(); i++)
    {
		QString d = jReceiveAddresses[i];
        QRegExp rxs("(\\:)");
        QStringList ds = d.split(rxs);

		item = new QStandardItem(ds[0]);
        model->setItem(i, 0, item);
        item = new QStandardItem(ds[1]);
        model->setItem(i, 1, item);
	}
	
   model->setHorizontalHeaderLabels(horizontalHeader);
   ui->tableView->setModel(model);
   ui->tableView->resizeRowsToContents();
   ui->tableView->resizeColumnsToContents();
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
	QMessageBox::critical(this, "", "QString text = ui->textEdit_3->toPlainText();");
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
}

void MainWindow::onAddRecipient()
{
	m_pRecipients->addItem();
}

void MainWindow::on_actionInformation_triggered()
{
    jtool.show();
}

void MainWindow::on_actionDebug_console_triggered()
{
    jtool.show();
}

void MainWindow::on_actionNetwork_Monitor_triggered()
{
    jtool.show();
}

void MainWindow::on_actionPeers_list_triggered()
{
    jtool.show();
}

void MainWindow::on_actionWallet_Repair_triggered()
{
    jtool.show();
}

void MainWindow::on_actionOpen_URI_triggered()
{
    jUri.show();
}

void MainWindow::on_actionSign_message_triggered()
{
    jsign.show();
}

void MainWindow::on_actionVerify_message_triggered()
{
    jsign.show();
}

void MainWindow::on_actionReceiving_addresses_triggered()
{
    jReceive.show();
}

void MainWindow::on_actionSending_addresses_triggered()
{
    jSendingAddressList.show();
}
