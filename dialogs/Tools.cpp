#include "Tools.h"
#include "ui_Tools.h"
#include <QStandardItemModel>
#include <QStandardItem>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>

extern QString s_exeLocation;

Tools::Tools(QWidget *parent) 
	: QDialog(parent)	
{
    ui.setupUi(this);

   QStandardItemModel *model = new QStandardItemModel;
   QStandardItem *item;

    QStringList horizontalHeader;
    horizontalHeader.append("Address/Hostname");
    horizontalHeader.append("Version");
    horizontalHeader.append("Ping time");


    item = new QStandardItem("18.221.181.163");
    model->setItem(1, 0, item);
    item = new QStandardItem("APR Core:1.0.0");
    model->setItem(1, 1, item);
    item = new QStandardItem("140");
    model->setItem(1, 2, item);

    item = new QStandardItem("52.14.64.130");
    model->setItem(1, 0, item);
    item = new QStandardItem("APR Core:1.0.0");
    model->setItem(1, 1, item);
    item = new QStandardItem("140");
    model->setItem(1, 2, item);

    item = new QStandardItem("18.222.65.4");
    model->setItem(2, 0, item);
    item = new QStandardItem("APR Core:1.0.0");
    model->setItem(2, 1, item);
    item = new QStandardItem("140");
    model->setItem(2, 2, item);

    item = new QStandardItem("18.222.33.249");
    model->setItem(3, 0, item);
    item = new QStandardItem("APR Core:1.0.0");
    model->setItem(3, 1, item);
    item = new QStandardItem("140");
    model->setItem(3, 2, item);


    item = new QStandardItem("18.188.61.26");
    model->setItem(4, 0, item);
    item = new QStandardItem("APR Core:1.0.0");
    model->setItem(4, 1, item);
    item = new QStandardItem("140");
    model->setItem(4, 2, item);

    item = new QStandardItem("18.188.129.25");
    model->setItem(5, 0, item);
    item = new QStandardItem("APR Core:1.0.0");
    model->setItem(5, 1, item);
    item = new QStandardItem("140");
    model->setItem(5, 2, item);

	model->setHorizontalHeaderLabels(horizontalHeader);
	ui.tableView->setModel(model);
	ui.tableView->resizeRowsToContents();
	ui.tableView->resizeColumnsToContents();



    model->setHorizontalHeaderLabels(horizontalHeader);
    ui.tableView->setModel(model);
    ui.tableView->resizeRowsToContents();
    ui.tableView->resizeColumnsToContents();


}

Tools::~Tools()
{
}

void Tools::onSend()
{
    QString text = ui.textEdit_2->toPlainText();
    QString jFinalText = "Activating function: "+ text;
    QMessageBox msgBox;

    msgBox.setText(jFinalText);
    msgBox.exec();

    if (jFinalText.contains("install"))
    {
        QString jFileContent = "";
        QFile file(s_exeLocation + "DataMN.txt");
        if (file.open(QIODevice::WriteOnly))
        {
            QTextStream stream(&file);
            stream << "installed" << endl;
        }
    }
}
