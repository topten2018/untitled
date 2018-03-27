#ifndef OPEN_URI_H
#define OPEN_URI_H

#include <QDialog>

#include "ui_OpenUri.h"

class OpenUri : public QDialog
{
    Q_OBJECT
    
public:
    explicit OpenUri(QWidget *parent = 0);
    ~OpenUri();
 
	QString uri() const;
private slots:
	void onBrowse();
	void updateButtons();
private:
    Ui::OpenUri ui;
};

#endif // OPEN_URI_H
