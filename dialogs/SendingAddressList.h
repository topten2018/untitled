#ifndef SENDINGADDRESSLIST_H
#define SENDINGADDRESSLIST_H

#include <QDialog>
#include "ui_sendingaddresslist.h"

class AdressBookModel;

class QMenu;

class SendingAddressList : public QDialog
{
    Q_OBJECT
    
public:
    explicit SendingAddressList(AdressBookModel * pModel, QWidget *parent = Q_NULLPTR);
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

	AdressBookModel * m_pModel;

	QMenu *m_pContextMenu;
};

#endif // SENDINGADDRESSLIST_H
