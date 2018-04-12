#ifndef DLGMULTISEND_H
#define DLGMULTISEND_H

#include <QDialog>
#include "ui_DlgMultisend.h"

class DlgMultisend : public QDialog
{
	Q_OBJECT

public:
	DlgMultisend(QWidget *parent = Q_NULLPTR);
	~DlgMultisend();

private:
	Ui::DlgMultisend ui;
};

#endif // DLGMULTISEND_H