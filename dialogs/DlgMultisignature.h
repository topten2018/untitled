#pragma once

#include <QDialog>
#include "ui_DlgMultisignature.h"

class AddressKeyModel;
class DestinationModel;
class TxHashModel;
class KeyModel;

class DlgMultisignature : public QDialog
{
	Q_OBJECT

public:
	DlgMultisignature(QWidget *parent = Q_NULLPTR);
	~DlgMultisignature();

	enum Pages
	{
		CreatePage = 0,
		CreateTxPage,
		SignTxPage
	};

public slots:
	void show(int i);

private slots:
	void onAddAddress();
	void onAddDestination();
	void onAddRawInput();
	void onAddPrivateKey();
	void updateButtons();
private:
	Ui::DlgMultisignature ui;

	AddressKeyModel		*m_pAddressModel;
	DestinationModel	*m_pDestinationModel;
	TxHashModel			*m_pTxHashModel;
	KeyModel			*m_pKeyModel;
};
