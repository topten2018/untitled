#ifndef TOOLS_H
#define TOOLS_H

#include <QtWidgets/QDialog>

namespace Ui {
class tools;
}

class tools : public QDialog
{
    Q_OBJECT
    
public:
    explicit tools(QWidget *parent = 0);
    ~tools();
    
private:
    Ui::tools *ui;
};

#endif // TOOLS_H
