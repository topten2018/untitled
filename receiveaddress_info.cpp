#include "receiveaddress_info.h"
#include "ui_receiveaddress_info.h"
#include "sockettest.h"
#include <QMessageBox>
#include <QTimer>
#include <QClipboard>

ReceiveAddress_Info::ReceiveAddress_Info(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ReceiveAddress_Info)
{
    ui->setupUi(this);
    QTimer *timer = new QTimer;
    connect(timer,SIGNAL(timeout()), this, SLOT(UpdateTextEdit()));
    timer->start(100);



}
void ReceiveAddress_Info::UpdateTextEdit()
{
    if (jAddressInfo.contains(":"))
    {
    QRegExp rxa("(\\:)");
    QStringList query = jAddressInfo.split(rxa);
    QString b = "Payment Information:\r\nURI:APR:"+ query[1];
    QString c = "\r\nAddress:"+query[1];
    QString d = b+c;
    jAddressInClipboard=query[1];
    jAddressInUri="APR:"+query[1];
    ui->textEdit->setText(d);
    this->setWindowTitle("Request payment to "+ query[1]);
    }
}

ReceiveAddress_Info::~ReceiveAddress_Info()
{
    delete ui;

}

void ReceiveAddress_Info::on_pushButton_clicked()
{
QClipboard *clipboard = QApplication::clipboard();
QString b = jAddressInUri;
clipboard->setText(b);
}

void ReceiveAddress_Info::on_pushButton_2_clicked()
{
    QClipboard *clipboard = QApplication::clipboard();
    QString b = jAddressInClipboard;
    clipboard->setText(b);
}

void ReceiveAddress_Info::on_pushButton_3_clicked()
{
    this->close();
}
