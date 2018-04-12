#ifndef DLGASKPASSPHRASE_H
#define DLGASKPASSPHRASE_H

#include <QDialog>
#include "ui_DlgAskPassphrase.h"

class WalletStorage;

class DlgAskPassphrase : public QDialog
{
	Q_OBJECT

public:
	enum class Mode {
		Encrypt,         /**< Ask passphrase twice and encrypt */
		UnlockAnonymize, /**< Ask passphrase and unlock only for anonymization */
		Unlock,          /**< Ask passphrase and unlock */
		ChangePass,      /**< Ask old passphrase + new passphrase twice */
		Decrypt          /**< Ask passphrase and decrypt wallet */
	};

	DlgAskPassphrase(Mode mode, WalletStorage * pStorage, QWidget *parent = Q_NULLPTR);
	~DlgAskPassphrase();

private slots:
	void updateButtons();
	void onAccept();
private:
	Ui::DlgAskPassphrase ui;

	Mode m_Mode;
	WalletStorage *m_pWalletStorage;
};

#endif // DLGASKPASSPHRASE_H
