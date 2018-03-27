#include "open_uri.h"
#include "ui_open_uri.h"

Open_URI::Open_URI(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Open_URI)
{
    ui->setupUi(this);
}

Open_URI::~Open_URI()
{
    delete ui;
}
