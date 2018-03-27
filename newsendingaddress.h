#ifndef NEWSENDINGADDRESS_H
#define NEWSENDINGADDRESS_H

#include <QtWidgets/QDialog>

namespace Ui {
class newsendingaddress;
}

class newsendingaddress : public QDialog
{
    Q_OBJECT
    
public:
    explicit newsendingaddress(QWidget *parent = 0);
    ~newsendingaddress();
    
private:
    Ui::newsendingaddress *ui;
};

#endif // NEWSENDINGADDRESS_H
