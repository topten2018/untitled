#ifndef DLGADDRESS_H
#define DLGADDRESS_H

#include <QDialog>
#include "ui_DlgAddress.h"
#include "items/AddressItem.h"


class DlgAddress : public QDialog
{
	Q_OBJECT

public:
	DlgAddress(const AddressItem * p, QWidget *parent = Q_NULLPTR);
	~DlgAddress();

	AddressItem address();
private:
	Ui::DlgAddress ui;
	AddressItem m_Address;
};
#endif // DLGADDRESS_H