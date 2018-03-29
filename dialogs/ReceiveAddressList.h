#ifndef RECEIVEADDRESSLIST_H
#define RECEIVEADDRESSLIST_H

#include "ui_ReceiveAddressList.h"

#include <QDialog>

class AddressBookModel;

class ReceiveAddressList : public QDialog
{
    Q_OBJECT
    
public:
    explicit ReceiveAddressList(AddressBookModel * pModel, QWidget *parent = nullptr);
    ~ReceiveAddressList();

private slots:
	void onAdd();
	void onEdit();
	void onCopy();
	void onCopyLabel();
	void onExport();

	void updateButtons();

	void customMenuRequested(const QPoint&);
private:
    Ui::ReceiveAddressList ui;

	AddressBookModel	*m_pModel;
	QMenu				*m_pContextMenu;
};

#endif // RECEIVEADDRESSLIST_H
