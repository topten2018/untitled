#include "zipvcontrol.h"
#include "ui_zipvcontrol.h"

zipvcontrol::zipvcontrol(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::zipvcontrol)
{
    ui->setupUi(this);
}

zipvcontrol::~zipvcontrol()
{
    delete ui;
}
