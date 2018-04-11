#ifndef TOOLS_H
#define TOOLS_H

#include <QDialog>
#include "ui_Tools.h"

class Tools : public QDialog
{
    Q_OBJECT
    
public:
	Tools(QWidget *parent = 0);
    ~Tools();
    
private slots:
    void onSend();

private:
    Ui::Tools ui;
};

#endif // TOOLS_H
