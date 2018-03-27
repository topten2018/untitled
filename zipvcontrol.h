#ifndef ZIPVCONTROL_H
#define ZIPVCONTROL_H

#include <QWidget>

namespace Ui {
class zipvcontrol;
}

class zipvcontrol : public QWidget
{
    Q_OBJECT
    
public:
    explicit zipvcontrol(QWidget *parent = 0);
    ~zipvcontrol();
    
private:
    Ui::zipvcontrol *ui;
};

#endif // ZIPVCONTROL_H
