#include "WalletStorage.h"

#include <QClipboard>
#include <QFile>
#include <QCryptographicHash>
#include <QFileInfo>
#include <QDir>

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

const char g_szPassphrase[] = "asd;fka28sdkmaswk3qwer457faksdfl;ksad09fkklasdjf238kjsblkjiorhjiuhwaeq8021";

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
	, m_iFlags(0)
{

}

WalletStorage::~WalletStorage()
{
	save();
}

bool WalletStorage::copy(const QString & filename)
{
	if (m_strFilename.isEmpty())
		return false;

	QFile::copy(m_strFilename, filename);

	return true;
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
		si.m_nFlags = Flags::Encrypted;
	else
		si.m_nFlags = 0;
	
	si.m_nFiles = FileTypes::Count;

	file.write((const char*)&si, sizeof(si));
	
	if (si.m_nFlags && Flags::Encrypted)
	{
		QCryptographicHash hash(QCryptographicHash::Sha256);
		hash.addData(m_strPassphrase.toLocal8Bit());
		hash.addData(QString(g_szPassphrase).toLocal8Bit());
		m_arrHash = hash.result();
		qint64 i = m_arrHash.size();
		file.write((const char*)&i, sizeof(i));
		file.write(m_arrHash);
	}

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

bool WalletStorage::open(const QString & filename)
{
	QMutexLocker locker(&m_mtx);

	QFileInfo fi(filename);
	if (!fi.exists())
	{
		if (!create(filename))
			return false;
	}

	m_strFilename = filename;

	QFile file(filename);
	if (!file.open(QFile::ReadOnly))
		return false;

	sStorageInfo si;

	file.read((char*)&si, sizeof(si));
	if (si.m_nType != 'WRPA')
		return false;

	if (si.m_nVersion != CURRENT_VERSION)
		return false;

	if (si.m_nFlags && Flags::Encrypted)
	{
		qint64 i;
		file.read((char *)&i, sizeof(i));
		m_arrHash = file.read(i);
	}

	m_iFlags = si.m_nFlags;

	QList<sFileInfo> lst;

	for (int i = 0; i < WalletStorage::Count; i++)
	{
		sFileInfo fi;
		file.read((char*)&fi, sizeof(sFileInfo));
		lst.append(fi);
	}

	return true;
}

bool WalletStorage::save()
{
	QMutexLocker locker(&m_mtx);

	if (m_strFilename.isEmpty())
		return true;

	QFile file(m_strFilename);
	if (!file.open(QFile::WriteOnly))
		return false;

	sStorageInfo si = { 0 };
	si.m_nType = 'WRPA';
	si.m_nVersion = CURRENT_VERSION;

	if (m_strPassphrase != g_szPassphrase)
		si.m_nFlags = Flags::Encrypted;
	else
		si.m_nFlags = 0;
	
	si.m_nFiles = FileTypes::Count;
	file.write((const char*)&si, sizeof(si));

	m_iFlags = si.m_nFlags;
	if (si.m_nFlags && Flags::Encrypted)
	{		
		QCryptographicHash hash(QCryptographicHash::Sha256);
		hash.addData(m_strPassphrase.toLocal8Bit());
		hash.addData(QString(g_szPassphrase).toLocal8Bit());
		m_arrHash = hash.result();
		qint64 i = m_arrHash.size();
		file.write((const char*)&i, sizeof(i));
		file.write(m_arrHash);
	}

	for (int i = 0; i < WalletStorage::Count; i++)
	{
		sFileInfo fi = { 0 };
		file.write((const char*)&fi, sizeof(fi));
	}
	for (int i = 0; i < WalletStorage::Count; i++)
	{
		if (!writeFile(file, WalletStorage::FileTypes(i)))
			return true;
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
	
	if (si.m_nFlags && Flags::Encrypted)
	{
		qint64 i;
		file.read((char *)&i, sizeof(i));
		m_arrHash = file.read(i);
	}

	m_iFlags = si.m_nFlags;

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

	int offset = sizeof(sStorageInfo);
	if (m_iFlags & Flags::Encrypted)
	{
		offset += m_arrHash.size() + sizeof(qint64);
	}

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
	file.seek(offset + sizeof(sFileInfo)*t);
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

int WalletStorage::flags()
{	
	return m_iFlags;
}

bool WalletStorage::setWalletEncrypted(bool encrypted, const QString& passphrase)
{
	QMutexLocker locker(&m_mtx);
	if (encrypted && g_szPassphrase != passphrase)
	{
		m_iFlags |= Flags::Encrypted;
		m_strPassphrase = passphrase;

		QCryptographicHash hash(QCryptographicHash::Sha256);
		hash.addData(m_strPassphrase.toLocal8Bit());
		hash.addData(QString(g_szPassphrase).toLocal8Bit());
		m_arrHash = hash.result();
		
		return true;
	}
	else 
	{
		if (checkPass(passphrase))
		{
			m_iFlags &= ~Flags::Encrypted;
			m_strPassphrase = g_szPassphrase;
			return true;
		}
		else
			return false;
	}
}

bool WalletStorage::checkPass(const QString & str)
{
	QCryptographicHash hash(QCryptographicHash::Sha256);
	hash.addData(str.toLocal8Bit());
	hash.addData(QString(g_szPassphrase).toLocal8Bit());
	if (hash.result() != m_arrHash)
		return false;
	return 
		true;
	
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
	if (!(m_iFlags & Flags::Encrypted) || ((m_iFlags & Flags::Encrypted) && checkPass(oldPass)))
	{
		m_strPassphrase = newPass;
		m_iFlags |= Flags::Encrypted;

		QCryptographicHash hash(QCryptographicHash::Sha256);
		hash.addData(m_strPassphrase.toLocal8Bit());
		hash.addData(QString(g_szPassphrase).toLocal8Bit());
		m_arrHash = hash.result();
		return true;
	}
	else
		return false;
}
