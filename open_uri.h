#ifndef OPEN_URI_H
#define OPEN_URI_H

#include <QtWidgets/QDialog>

namespace Ui {
class Open_URI;
}

class Open_URI : public QDialog
{
    Q_OBJECT
    
public:
    explicit Open_URI(QWidget *parent = 0);
    ~Open_URI();
    
private:
    Ui::Open_URI *ui;
};

#endif // OPEN_URI_H
