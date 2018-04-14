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
		Encrypted = 1,
	};

	WalletStorage();
	~WalletStorage();

	
	bool open(const QString & filename);
	bool copy(const QString & filename);
	int  flags();
	bool restore(const QString & res);

	// Wallet encryption
	bool setWalletEncrypted(bool encrypted, const QString & passphrase);
	// Passphrase only needed when unlocking
	bool setWalletLocked(bool locked, const QString& passPhrase = QString(), bool anonymizeOnly = false);
	bool changePassphrase(const QString& oldPass, const QString& newPass);
	// Is wallet unlocked for anonymization only?
	bool isAnonymizeOnlyUnlocked();
	bool save();
private:
	bool writeFile(QFile & file, WalletStorage::FileTypes t);
	bool readFile(QFile & file, const sFileInfo *);
	bool create(const QString & dst);

	bool checkPass(const QString & str);

	QString			m_strPassphrase;
	QByteArray		m_arrHash;
	int				m_iFlags;
	QString			m_strFilename;

	mutable QMutex	m_mtx;
};

#endif //WALLETSTORAGE_H