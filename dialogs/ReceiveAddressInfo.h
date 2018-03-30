#ifndef RECEIVEADDRESSINFO_H
#define RECEIVEADDRESSINFO_H

#include <QDialog>
#include "ui_ReceiveAddressInfo.h"
#include "items/TransactionItem.h"
#include "widgets/QrCodeImage.h"

class ReceiveAddressInfo : public QDialog
{
    Q_OBJECT
    
public:
    explicit ReceiveAddressInfo(const TransactionItem & ti, QWidget *parent = 0);
    ~ReceiveAddressInfo();

private slots:
    void onCopyUri();
    void onCopyAddress();
	void onSaveImage();
	void onCopyImage();

	void showImageMenu(const QPoint&);
private:
    Ui::ReceiveAddressInfo ui;

	TransactionItem m_TransactionItem;
	QrCodeImage		m_QrCode;

	QMenu		   *m_pImageMenu;
};

#endif // RECEIVEADDRESSINFO_H
