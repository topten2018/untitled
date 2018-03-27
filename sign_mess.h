#ifndef SIGN_MESS_H
#define SIGN_MESS_H

#include <QDialog>

namespace Ui {
class Sign_Mess;
}

class Sign_Mess : public QDialog
{
    Q_OBJECT
    
public:
    explicit Sign_Mess(QWidget *parent = 0);
    ~Sign_Mess();
    
private:
    Ui::Sign_Mess *ui;
};

#endif // SIGN_MESS_H
