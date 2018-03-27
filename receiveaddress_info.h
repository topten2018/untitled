#ifndef RECEIVEADDRESS_INFO_H
#define RECEIVEADDRESS_INFO_H

#include <QtWidgets/QDialog>

namespace Ui {
class ReceiveAddress_Info;
}

class ReceiveAddress_Info : public QDialog
{
    Q_OBJECT
    
public:
    explicit ReceiveAddress_Info(QWidget *parent = 0);
    ~ReceiveAddress_Info();
    private slots:
    void UpdateTextEdit();
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::ReceiveAddress_Info *ui;
};

#endif // RECEIVEADDRESS_INFO_H
