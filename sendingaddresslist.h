#ifndef SENDINGADDRESSLIST_H
#define SENDINGADDRESSLIST_H

#include <QtWidgets/QDialog>

namespace Ui {
class SendingAddressList;
}

class SendingAddressList : public QDialog
{
    Q_OBJECT
    
public:
    explicit SendingAddressList(QWidget *parent = 0);
    ~SendingAddressList();
    bool jRefresh;
   private slots:
    void UpdateTextEdit();
private:
    Ui::SendingAddressList *ui;
};

#endif // SENDINGADDRESSLIST_H
