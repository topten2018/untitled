#include "sendingaddresslist.h"
#include "ui_sendingaddresslist.h"
#include <QStandardItemModel>
#include <QStandardItem>
#include <QMessageBox>
#include "sockettest.h"
#include <QTimer>
#include <QString>

SendingAddressList::SendingAddressList(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SendingAddressList)
{
    ui->setupUi(this);
    QStandardItemModel *model2 = new QStandardItemModel;
    QStandardItem *item2;

    QStringList horizontalHeader;
    horizontalHeader.append("Label");
    horizontalHeader.append("Address");

    model2->setHorizontalHeaderLabels(horizontalHeader);


    if (jSendingAddressesOUTList.contains(":"))
    {


        QRegExp rxad("(\\;)");
        QStringList query2 = jSendingAddressesOUTList.split(rxad);

        for (int x = 0; x<query2.count(); x++)
        {

            QRegExp rxa("(\\:)");
            QStringList query = query2[x].split(rxa);
            item2 = new QStandardItem(query[1]);
            model2->setItem(x+1, 1, item2);   // address
            item2 = new QStandardItem(query[0]);
            model2->setItem(x+1, 0, item2);   // label
        }





     }



  //  ui->setWindowTitle("Request payment to ");


















    ui->tableView->setModel(model2);
    ui->tableView->resizeRowsToContents();
    ui->tableView->resizeColumnsToContents();

   QTimer *timer = new QTimer;
   connect(timer,SIGNAL(timeout()), this, SLOT(UpdateTextEdit()));
   timer->start(100);


}

bool jRefresh = false;

void SendingAddressList::UpdateTextEdit()
{
    if (jRefresh==false)

    {
    QStandardItemModel *model2 = new QStandardItemModel;
    QStandardItem *item2;

    QStringList horizontalHeader;
    horizontalHeader.append("Label");
    horizontalHeader.append("Address");
    model2->setHorizontalHeaderLabels(horizontalHeader);

QString jSendingAddressesOUTListTemp = jSendingAddressesOUTList;
    if (jSendingAddressesOUTListTemp.contains(":"))
    {

        jRefresh = true;
        QRegExp rxad("(\\;)");
        QStringList query2 = jSendingAddressesOUTListTemp.split(rxad);

        for (int x = 0; x<query2.count(); x++)
        {

            QRegExp rxa("(\\:)");
            QStringList query = query2[x].split(rxa);
            item2 = new QStandardItem(query[1]);
            model2->setItem(x, 1, item2);   // address
            item2 = new QStandardItem(query[0]);
            model2->setItem(x, 0, item2);   // label
        }





     }




  //  ui->setWindowTitle("Request payment to ");


















    ui->tableView->setModel(model2);
    ui->tableView->resizeRowsToContents();
    ui->tableView->resizeColumnsToContents();

}

}

SendingAddressList::~SendingAddressList()
{
    delete ui;
}
