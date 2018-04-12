#ifndef WALLETSTORAGE_H
#define WALLETSTORAGE_H

#include <QMutex>
#include <QObject>
#include <QFile>

struct sFileInfo;

class WalletStorage : public QObject
{
	Q_OBJECT

public:
	enum FileTypes
	{
		AddressList = 0,
		SendingAddressList,
		Addresses,
		Count
	};

	enum Flags 
	{
		NoFlags = 0,
		Encripted = 1,
	};

	WalletStorage();
	~WalletStorage();

	void setPassphrase(const QString & passphrase);
		
	bool create(const QString & dst);
	int  flags(const QString & res);
	bool restore(const QString & res);

	// Wallet encryption
	bool setWalletEncrypted(bool encrypted, const QString & passphrase);
	// Passphrase only needed when unlocking
	bool setWalletLocked(bool locked, const QString& passPhrase = QString(), bool anonymizeOnly = false);
	bool changePassphrase(const QString& oldPass, const QString& newPass);
	// Is wallet unlocked for anonymization only?
	bool isAnonymizeOnlyUnlocked();
private:
	bool writeFile(QFile & file, WalletStorage::FileTypes t);
	bool readFile(QFile & file, const sFileInfo *);

	QString m_strPassphrase;

	mutable QMutex	m_mtx;
};

#endif //WALLETSTORAGE_H