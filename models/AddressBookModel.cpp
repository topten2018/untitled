#include "models/AddressBookModel.h"

#include "Utils/AutoSaver.h"
#include "Utils/StringUtils.h"

#include "dialogs/DlgAddress.h"

#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QMutexLocker>

AddressBookModel::AddressBookModel(Mode mode, const QString filename, QObject *parent)
	: QAbstractTableModel(parent)
	, m_strFileName(filename)
	, m_mtx(QMutex::Recursive)
	, m_Mode(mode)
{
	m_spAutoSaver = new AutoSaver(this);
	load();
}

AddressBookModel::~AddressBookModel()
{
	m_spAutoSaver->saveIfNeccessary();
	qDeleteAll(m_lstItems);
}
QVariant AddressBookModel::headerData(int section, Qt::Orientation , int role) const
{
	QVariant result;

	if (role != Qt::DisplayRole)
		return result;
	
	switch( section ) 
	{
	case H_LABEL:
		result = tr("Label");
		break;
	case H_ADDRESS:
		result = tr("Address");
		break;	
	};
	return result;
}
bool AddressBookModel::setData(const QModelIndex & index, const QVariant & value, int role)
{
	if (!index.isValid())
		return false;

	AddressItem * item = m_lstItems.at(index.row());

	if (role == Qt::EditRole)
	{
		switch (index.column())
		{
		case H_LABEL:
			item->setLabel(value.toString());
			m_spAutoSaver->changeOccurred();
			return true;
			break;
		case H_ADDRESS:
			item->setAddress(value.toString());
			m_spAutoSaver->changeOccurred();
			return true;
			break;
		}
	}

	return QAbstractTableModel::setData(index, value, role);
}
QVariant AddressBookModel::data(const QModelIndex & index,int role) const
{
	if (!index.isValid())
		return QVariant();

	const AddressItem * item = m_lstItems.at(index.row());

	switch (role)
	{
	case Qt::EditRole:
	{
		switch (index.column())
		{
		case H_LABEL:
			return item->label();
			break;
		case H_ADDRESS:
			return item->address();
			break;
		};
		return QVariant();
	}
	case Qt::DisplayRole:
	{
		switch (index.column())
		{
		case H_LABEL:
			return item->label();
			break;
		case H_ADDRESS:
			return item->address();
			break;		
		};
		break;
	}	
	}
	return QVariant();
}
Qt::ItemFlags AddressBookModel::flags(const QModelIndex &index) const
{
	if (!index.isValid())
		return QAbstractTableModel::flags(index);

	Qt::ItemFlags flags = QAbstractTableModel::flags(index);

	if (index.column() == H_LABEL || m_Mode == Mode::Send)
		return  flags | Qt::ItemIsEditable;
	
	return flags;
}
AddressItem * AddressBookModel::item(int row)
{
	return m_lstItems.at(row);
}
void AddressBookModel::onAddItem()
{
	DlgAddress dlg(nullptr, dynamic_cast<QWidget *>(parent()));

	if (dlg.exec() == QDialog::Accepted)
	{
		addItem(new AddressItem(dlg.address()));
		m_spAutoSaver->changeOccurred();
	}
}
void AddressBookModel::append(AddressItem * p)
{
	addItem(p);
	m_spAutoSaver->changeOccurred();
}
void AddressBookModel::onEditItem(int row)
{
	AddressItem * p = m_lstItems.at(row);
	if (!p)
		return;

	DlgAddress dlg(p, dynamic_cast<QWidget *>(parent()));

	if (dlg.exec() == QDialog::Accepted)
	{
		QMutexLocker locker(&m_mtx);
		*m_lstItems.at(row) = dlg.address();
		m_spAutoSaver->changeOccurred();
	}
}
void AddressBookModel::onDeleteItem(int row)
{
	QMessageBox mb(QMessageBox::Icon::Warning, tr("Warning"), tr("Delete this address?")
		, QMessageBox::StandardButton::Ok | QMessageBox::StandardButton::Cancel, dynamic_cast<QWidget *>(parent()));
	
	if (mb.exec() == QMessageBox::StandardButton::Ok)
	{
		QMutexLocker locker(&m_mtx);

		m_spAutoSaver->changeOccurred();
						
		beginRemoveRows(QModelIndex(), row, row);
		m_lstItems.removeAt(row);
		endRemoveRows();
	}
}
void AddressBookModel::addItem(AddressItem * p)
{
	QMutexLocker locker(&m_mtx);

	int row = m_lstItems.count();
	beginInsertRows(QModelIndex(), row, row);
	m_lstItems.append(p);
	endInsertRows();
}
void AddressBookModel::load()
{
	QMutexLocker locker(&m_mtx);

	qDeleteAll(m_lstItems);
	m_lstItems.clear();

	QFile file(m_strFileName);
	if (file.open(QIODevice::ReadOnly))
	{
		QTextStream in(&file);
		QStringList row;
		while (!in.atEnd())
		{
			QString line = in.readLine();
			if (Utils::parseCsvLine(line, row) && row.size() >= 2)
			{
				m_lstItems.append(new AddressItem(row[0], row[1]));
			}
		}
		file.close();
	}
}
void AddressBookModel::save() const
{
	saveToFile(m_strFileName, false);
}
void AddressBookModel::exportToFile(const QString & filename) const
{
	saveToFile(filename, true);
}
void AddressBookModel::saveToFile(const QString & filename, bool bWriteHeader) const
{
	QMutexLocker locker(&m_mtx);

	QFile file(filename);
	if (file.open(QIODevice::WriteOnly))
	{
		QTextStream out(&file);
		if (bWriteHeader)
		{
			QString line = QString("\"%1\",\"%2\"\r\n").arg("Label").arg("Address");
			out << line;
		}
		foreach (AddressItem * item, m_lstItems)
		{
			QString line = QString("\"%1\",\"%2\"\r\n").arg(item->label().replace("\"", "\"\"")).arg(item->address().replace("\"", "\"\""));
			out << line;
		}
		file.close();
	}
}