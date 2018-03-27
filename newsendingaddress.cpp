#include "newsendingaddress.h"
#include "ui_newsendingaddress.h"

newsendingaddress::newsendingaddress(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::newsendingaddress)
{
    ui->setupUi(this);
}

newsendingaddress::~newsendingaddress()
{
    delete ui;
}
