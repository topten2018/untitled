#pragma once

#include <QDialog>
#include "ui_DlgAdress.h"
#include "items/AdressItem.h"


class DlgAdress : public QDialog
{
	Q_OBJECT

public:
	DlgAdress(const AdressItem * p, QWidget *parent = Q_NULLPTR);
	~DlgAdress();

	AdressItem adress();
private:
	Ui::DlgAdress ui;
	AdressItem m_Adress;
};
