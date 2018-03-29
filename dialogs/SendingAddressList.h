#ifndef SENDINGADDRESSLIST_H
#define SENDINGADDRESSLIST_H

#include <QDialog>
#include "ui_sendingaddresslist.h"

class AddressBookModel;

class QMenu;

class SendingAddressList : public QDialog
{
    Q_OBJECT
    
public:
    explicit SendingAddressList(AddressBookModel * pModel, QWidget *parent = Q_NULLPTR);
    ~SendingAddressList();

private slots:
	void onAdd();
	void onDelete();
	void onEdit();
	void onCopy();
	void onCopyLabel();
	void onExport();

	void updateButtons();

	void customMenuRequested(const QPoint&);
private:
    Ui::SendingAddressList ui;

	AddressBookModel * m_pModel;

	QMenu *m_pContextMenu;
};

#endif // SENDINGADDRESSLIST_H
