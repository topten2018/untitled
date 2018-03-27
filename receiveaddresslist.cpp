#include "receiveaddresslist.h"
#include "ui_receiveaddresslist.h"
#include <QStandardItemModel>
#include <QStandardItem>
#include <QMessageBox>
#include "sockettest.h"
#include <QTimer>
#include <QString>

Receiveaddresslist::Receiveaddresslist(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Receiveaddresslist)
{
    ui->setupUi(this);



    QTimer *timer = new QTimer;
    connect(timer,SIGNAL(timeout()), this, SLOT(UpdateTable()));
    timer->start(5000);












    QStandardItemModel *model2 = new QStandardItemModel;
    QStandardItem *item2;

    QStringList horizontalHeader;
    horizontalHeader.append("Label");
    horizontalHeader.append("Address");

    model2->setHorizontalHeaderLabels(horizontalHeader);
    ui->tableView->setModel(model2);
    ui->tableView->resizeRowsToContents();
    ui->tableView->resizeColumnsToContents();




    if (!jStatisticsHistory.isEmpty())
    {
    QRegExp rxa("(\\;)");
    QStringList query = jStatisticsHistory.split(rxa);



    for (int i =2; i<query.count()-1; i++)
    {
        QString d = query[i];
        QRegExp rxs("(\\:)");
        QStringList ds = d.split(rxs);

        /*
        QMessageBox msgBox;
        msgBox.setText("This "+ d);
        msgBox.exec();
        */



        item2 = new QStandardItem(ds[1]);
        model2->setItem(i-2, 1, item2);   // address




    }


    }


    model2->setHorizontalHeaderLabels(horizontalHeader);
    ui->tableView->setModel(model2);
    ui->tableView->resizeRowsToContents();
    ui->tableView->resizeColumnsToContents();
    connect(ui->tableView, SIGNAL(clicked(const QModelIndex&)), this, SLOT(onTableClicked()));
}

bool jRefresh2 = false;

void Receiveaddresslist::UpdateTable()
{

    if (jRefresh2==false)
    {
    QStandardItemModel *model2 = new QStandardItemModel;
    QStandardItem *item2;

    QStringList horizontalHeader;
    horizontalHeader.append("Label");
    horizontalHeader.append("Address");

    model2->setHorizontalHeaderLabels(horizontalHeader);


QString jStatisticsHistoryTMP = jStatisticsHistory;
    if (!jStatisticsHistoryTMP.isEmpty())
    {
       jRefresh2 = true;
    QRegExp rxa("(\\;)");
    QStringList query = jStatisticsHistoryTMP.split(rxa);



    for (int i =2; i<query.count()-1; i++)
    {
        QString d = query[i];
        QRegExp rxs("(\\:)");
        QStringList ds = d.split(rxs);

        /*
        QMessageBox msgBox;
        msgBox.setText("This "+ d);
        msgBox.exec();
        */



        item2 = new QStandardItem(ds[1]);
        model2->setItem(i-2, 1, item2);   // address




    }


    }


    model2->setHorizontalHeaderLabels(horizontalHeader);
    ui->tableView->setModel(model2);
    ui->tableView->resizeRowsToContents();
    ui->tableView->resizeColumnsToContents();
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
}


}

void Receiveaddresslist::onTableClicked()
{
    QModelIndex index = ui->tableView->currentIndex();
    int i = index.row(); // now you know which record was selected
    QString j =QString::number(i);

    QMessageBox msgBox;
    msgBox.setText("This "+ j);
    msgBox.exec();

}
Receiveaddresslist::~Receiveaddresslist()
{
    delete ui;
}
