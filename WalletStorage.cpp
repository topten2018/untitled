#include "WalletStorage.h"

#include <QClipboard>
#include <QFile>

#define BLOCK_SIZE 1024*1024

extern QString s_exeLocation;

const char * g_Filenames[] = {
	"AddressList.txt",
	"SendingAddressList.txt",
	"Addresses.txt"
};
const char * g_Filenames_bak[] = {
	"AddressList.txt.bak",
	"SendingAddressList.txt.bak",
	"Addresses.txt.bak"
};

const char g_szPassphrase[] = "asd;fka28sdkmaswk3457faksdfl;ksad09fkklasdjf238kjsblkjiorhjiuhwaeq8021";

#define VERSION_1 1
#define CURRENT_VERSION VERSION_1

struct sStorageInfo
{
	qint32 m_nType;
	qint16 m_nVersion;
	qint16 m_nFlags;
	qint32 m_nFiles;
	qint32 m_nDummi;
};

struct sFileInfo 
{
	qint32 m_nType;
	qint32 m_nBlocks;
	qint64 m_nFileSize;
	qint64 m_nOffset;
	qint64 m_nSize;
};
struct sBlockInfo
{
	qint64 m_nOffset;
	qint64 m_nSize;
};

WalletStorage::WalletStorage()
	: m_mtx(QMutex::RecursionMode::Recursive)
	, m_strPassphrase(g_szPassphrase)
{

}

WalletStorage::~WalletStorage()
{

}

bool WalletStorage::create(const QString & dst)
{
	QMutexLocker locker(&m_mtx);

	QFile file(dst);
	if (!file.open(QFile::WriteOnly))
		return false;

	sStorageInfo si = {0};
	si.m_nType = 'WRPA';
	si.m_nVersion = CURRENT_VERSION;

	if (m_strPassphrase != g_szPassphrase)
		si.m_nFlags = Flags::Encripted;
	else
		si.m_nFlags = 0;

	si.m_nFiles = FileTypes::Count;

	file.write((const char*)&si, sizeof(si));
	for (int i = 0; i < WalletStorage::Count; i++)
	{
		sFileInfo fi = {0};
		file.write((const char*)&fi, sizeof(fi));
	}
	for (int i = 0; i < WalletStorage::Count; i++)
	{
		if (!writeFile(file, WalletStorage::FileTypes(i)))
			return true;;
	}
	return true;
}
bool WalletStorage::restore(const QString & res)
{
	QMutexLocker locker(&m_mtx);

	QFile file(res);
	if (!file.open(QFile::ReadOnly))
		return false;

	sStorageInfo si;
	
	file.read((char*)&si, sizeof(si));
	if (si.m_nType != 'WRPA')
		return false;

	if (si.m_nVersion != CURRENT_VERSION)
		return false;

	QList<sFileInfo> lst;

	for (int i = 0; i < WalletStorage::Count; i++)
	{
		sFileInfo fi;
		file.read((char*)&fi, sizeof(sFileInfo));
		lst.append(fi);
	}
	for (int i = 0; i < WalletStorage::Count; i++)
	{
		if (!readFile(file, &lst.at(i)))
			return true;
	}
	return true;
}
bool WalletStorage::writeFile(QFile & file, WalletStorage::FileTypes t)
{
	QString filename = s_exeLocation + g_Filenames[t];

	QFile dst(filename);
	if (!dst.open(QFile::ReadOnly))
		return false;

	sFileInfo fi;
	fi.m_nType = t;
	fi.m_nBlocks = 0;
	fi.m_nFileSize = dst.size();
	fi.m_nOffset = file.pos();
	fi.m_nSize = 0;

	while (!dst.atEnd()) 
	{
		QByteArray arr = dst.read(BLOCK_SIZE);
		QByteArray arr2 = qCompress(arr);
		for (int i = 0, j = 0; i < arr2.size(); i++, j++)
		{
			arr2[i] = ((char)arr2[i]) ^ m_strPassphrase[j].toLatin1();
			if (j >= m_strPassphrase.size())
				j = 0;
		}
		
		fi.m_nBlocks++;
		fi.m_nSize += arr2.size();
		
		sBlockInfo bi;
		bi.m_nOffset = file.pos();
		bi.m_nSize = arr2.size();

		file.write((const char *)&bi, sizeof(bi));
		file.write(arr2);
	}
	qint64 pos = file.pos();
	file.seek(sizeof(sStorageInfo) + sizeof(sFileInfo)*t);
	file.write((const char *)&fi, sizeof(sFileInfo));
	file.seek(pos);

	return true;
}
bool WalletStorage::readFile(QFile & file, const sFileInfo * fi)
{
	QString filename = s_exeLocation + g_Filenames_bak[fi->m_nType];
	
	QFile dst(filename);
	if (!dst.open(QFile::WriteOnly))
		return false;

	file.seek(fi->m_nOffset);

	for (int i = 0; i < fi->m_nBlocks; i++)
	{
		sBlockInfo bi;
		file.read((char*)&bi, sizeof(bi));

		QByteArray arr = file.read(bi.m_nSize);		
		for (int i = 0, j = 0; i < arr.size(); i++, j++)
		{
			arr[i] = ((char)arr[i]) ^ m_strPassphrase[j].toLatin1();
			if (j >= m_strPassphrase.size())
				j = 0;
		}
		QByteArray arr2 = qUncompress(arr);

		dst.write(arr2);
	}

	return true;
}
void WalletStorage::setPassphrase(const QString & passphrase)
{
	m_strPassphrase = passphrase;
}

int WalletStorage::flags(const QString & res)
{
	QMutexLocker locker(&m_mtx);

	QFile file(res);
	if (!file.open(QFile::ReadOnly))
		return 0;

	sStorageInfo si;

	file.read((char*)&si, sizeof(si));
	if (si.m_nType != 'WRPA')
		return 0;

	if (si.m_nVersion != CURRENT_VERSION)
		return 0;

	return si.m_nFlags;
}


bool WalletStorage::setWalletEncrypted(bool encrypted, const QString& passphrase)
{
	QMutexLocker locker(&m_mtx);
	if (encrypted) 
	{
		// Encrypt
		return true;// wallet->EncryptWallet(passphrase);
	}
	else {
		// Decrypt -- TODO; not supported yet
		return false;
	}
}

bool WalletStorage::setWalletLocked(bool locked, const QString& passPhrase, bool anonymizeOnly)
{
	QMutexLocker locker(&m_mtx);
	if (locked) 
	{
		// Lock
		//wallet->fWalletUnlockAnonymizeOnly = false;
		return true;//wallet->Lock();
	}
	else {
		// Unlock
		return true;// wallet->Unlock(passPhrase, anonymizeOnly);
	}
}

bool WalletStorage::isAnonymizeOnlyUnlocked()
{
	QMutexLocker locker(&m_mtx);
	return true;// wallet->fWalletUnlockAnonymizeOnly;
}

bool WalletStorage::changePassphrase(const QString & oldPass, const QString& newPass)
{
	QMutexLocker locker(&m_mtx);
	bool retval;
	{
	//	LOCK(wallet->cs_wallet);
	//	wallet->Lock(); // Make sure wallet is locked before attempting pass change
		retval = true;//wallet->ChangeWalletPassphrase(oldPass, newPass);
	}
	return retval;
}
