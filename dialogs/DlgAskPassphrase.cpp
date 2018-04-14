#include "DlgAskPassphrase.h"

#include <QMessageBox>
#include <QPushButton>

#include "WalletStorage.h"

DlgAskPassphrase::DlgAskPassphrase(Mode mode, WalletStorage *pStorage, QWidget *parent)
	: QDialog(parent)
	, m_Mode(mode)
	, m_pWalletStorage(pStorage)
{
	ui.setupUi(this);
		

	switch (mode) 
	{
	case Mode::Encrypt: // Ask passphrase x2
		ui.m_lWarning->setText(tr("Enter the new passphrase to the wallet.<br/>Please use a passphrase of <b>ten or more random characters</b>, or <b>eight or more words</b>."));
		ui.m_lPass1->hide();
		ui.m_lePass1->hide();
		setWindowTitle(tr("Encrypt wallet"));
		break;
	case Mode::UnlockAnonymize:
		ui.m_cbAnonymization->show();
	case Mode::Unlock: // Ask passphrase
		ui.m_lWarning->setText(tr("This operation needs your wallet passphrase to unlock the wallet."));
		ui.m_lPass2->hide();
		ui.m_lePass2->hide();
		ui.m_lPass3->hide();
		ui.m_lePass3->hide();
		setWindowTitle(tr("Unlock wallet"));
		break;
	case Mode::Decrypt: // Ask passphrase
		ui.m_lWarning->setText(tr("This operation needs your wallet passphrase to decrypt the wallet."));
		ui.m_lPass2->hide();
		ui.m_lePass2->hide();
		ui.m_lPass3->hide();
		ui.m_lePass3->hide();
		setWindowTitle(tr("Decrypt wallet"));
		break;
	case Mode::ChangePass: // Ask old passphrase + new passphrase x2
		setWindowTitle(tr("Change passphrase"));
		ui.m_lWarning->setText(tr("Enter the old and new passphrase to the wallet."));
		break;
	}

	connect(ui.m_lePass1, SIGNAL(textChanged(QString)), this, SLOT(updateButtons()));
	connect(ui.m_lePass2, SIGNAL(textChanged(QString)), this, SLOT(updateButtons()));
	connect(ui.m_lePass3, SIGNAL(textChanged(QString)), this, SLOT(updateButtons()));

	updateButtons();
}

DlgAskPassphrase::~DlgAskPassphrase()
{
}

void DlgAskPassphrase::updateButtons()
{
	// Validate input, set Ok button to enabled when acceptable
	bool acceptable = false;
	switch (m_Mode) 
	{
	case Mode::Encrypt: // New passphrase x2
		acceptable = !ui.m_lePass2->text().isEmpty() && !ui.m_lePass3->text().isEmpty();
		break;
	case Mode::UnlockAnonymize: // Old passphrase x1
	case Mode::Unlock:          // Old passphrase x1
	case Mode::Decrypt:
		acceptable = !ui.m_lePass1->text().isEmpty();
		break;
	case Mode::ChangePass: // Old passphrase x1, new passphrase x2
		acceptable = !ui.m_lePass1->text().isEmpty() && !ui.m_lePass2->text().isEmpty() && !ui.m_lePass3->text().isEmpty();
		break;
	}
	ui.m_bbOkCancel->button(QDialogButtonBox::Ok)->setEnabled(acceptable);
}

void DlgAskPassphrase::onAccept()
{	
	QString oldPass  = ui.m_lePass1->text();
	QString newPass1 = ui.m_lePass2->text();
	QString newPass2 = ui.m_lePass3->text();
	switch (m_Mode) 
	{
	case Mode::Encrypt: 
	{
		if (newPass1.isEmpty() || newPass2.isEmpty())
		{
			// Cannot encrypt with empty passphrase
			break;
		}
		QMessageBox::StandardButton retval = QMessageBox::question(this, tr("Confirm wallet encryption"),
			tr("Warning: If you encrypt your wallet and lose your passphrase, you will <b>LOSE ALL OF YOUR APR</b>!") + "<br><br>" + tr("Are you sure you wish to encrypt your wallet?"),
			QMessageBox::Yes | QMessageBox::Cancel,
			QMessageBox::Cancel);
		if (retval == QMessageBox::Yes) 
		{
			if (newPass1 == newPass2) 
			{
				if (m_pWalletStorage->setWalletEncrypted(true, newPass1))
				{
					QMessageBox::warning(this, tr("Wallet encrypted"),
						"<qt>" +
						tr("APR Wallet will close now to finish the encryption process. "
							"Remember that encrypting your wallet cannot fully protect "
							"your APRs from being stolen by malware infecting your computer.") +
						"<br><br><b>" +
						tr("IMPORTANT: Any previous backups you have made of your wallet file "
							"should be replaced with the newly generated, encrypted wallet file. "
							"For security reasons, previous backups of the unencrypted wallet file "
							"will become useless as soon as you start using the new, encrypted wallet.") +
						"</b></qt>");
					QApplication::quit();
				}
				else 
				{
					QMessageBox::critical(this, tr("Wallet encryption failed"),
						tr("Wallet encryption failed due to an internal error. Your wallet was not encrypted."));
				}
				QDialog::accept(); // Success
			}
			else 
			{
				QMessageBox::critical(this, tr("Wallet encryption failed"),
					tr("The supplied passphrases do not match."));
			}
		}
		else 
		{
			QDialog::reject(); // Cancelled
		}
	} 
	break;
	case Mode::UnlockAnonymize:
	case Mode::Unlock:
		if (!m_pWalletStorage->setWalletLocked(false, oldPass, ui.m_cbAnonymization->isChecked()))
		{
			QMessageBox::critical(this, tr("Wallet unlock failed"),
				tr("The passphrase entered for the wallet decryption was incorrect."));
		}
		else 
		{
			QDialog::accept(); // Success
		}
		break;
	case Mode::Decrypt:
		if (!m_pWalletStorage->setWalletEncrypted(false, oldPass))
		{
			QMessageBox::critical(this, tr("Wallet decryption failed"),
				tr("The passphrase entered for the wallet decryption was incorrect."));
		}
		else
		{
			QDialog::accept(); // Success
		}
		break;
	case Mode::ChangePass:
		if (newPass1 == newPass2) {
			if (m_pWalletStorage->changePassphrase(oldPass, newPass1))
			{
				QMessageBox::information(this, tr("Wallet encrypted"),
					tr("Wallet passphrase was successfully changed."));
				QDialog::accept(); // Success
			}
			else 
			{
				QMessageBox::critical(this, tr("Wallet encryption failed"),
					tr("The passphrase entered for the wallet decryption was incorrect."));
			}
		}
		else
		{
			QMessageBox::critical(this, tr("Wallet encryption failed"),
				tr("The supplied passphrases do not match."));
		}
		break;
	}
}