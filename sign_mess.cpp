#include "sign_mess.h"
#include "ui_sign_mess.h"

Sign_Mess::Sign_Mess(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Sign_Mess)
{
    ui->setupUi(this);
}

Sign_Mess::~Sign_Mess()
{
    delete ui;
}
