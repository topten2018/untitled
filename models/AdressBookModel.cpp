#include "models/AdressBookModel.h"

#include "Utils/AutoSaver.h"
#include "Utils/StringUtils.h"

#include "dialogs/DlgAdress.h"

#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QMutexLocker>

AdressBookModel::AdressBookModel(const QString filename, QObject *parent)
	: QAbstractTableModel(parent)
	, m_strFileName(filename)
	, m_mtx(QMutex::Recursive)
{
	m_spAutoSaver = new AutoSaver(this);
	load();
}

AdressBookModel::~AdressBookModel()
{
	m_spAutoSaver->saveIfNeccessary();
	qDeleteAll(m_lstItems);
}
QVariant AdressBookModel::headerData(int section, Qt::Orientation , int role) const
{
	QVariant result;

	if (role != Qt::DisplayRole)
		return result;
	
	switch( section ) 
	{
	case H_LABEL:
		result = tr("Label");
		break;
	case H_ADRESS:
		result = tr("Adress");
		break;	
	};
	return result;
}
bool AdressBookModel::setData(const QModelIndex & index, const QVariant & value, int role)
{
	if (!index.isValid())
		return false;

	AdressItem * item = m_lstItems.at(index.row());

	if (role == Qt::EditRole && index.column() == H_LABEL)
	{
		item->setLabel(value.toString());
		m_spAutoSaver->changeOccurred();
		return true;
	}

	return QAbstractTableModel::setData(index, value, role);
}
QVariant AdressBookModel::data(const QModelIndex & index,int role) const
{
	if (!index.isValid())
		return QVariant();

	const AdressItem * item = m_lstItems.at(index.row());

	switch (role)
	{
	case Qt::EditRole:
	{
		if (index.column() == H_LABEL)
			return item->label();
		return QVariant();
	}
	case Qt::DisplayRole:
	{
		switch (index.column())
		{
		case H_LABEL:
			return item->label();
			break;
		case H_ADRESS:
			return item->adress();
			break;		
		};
		break;
	}	
	}
	return QVariant();
}
Qt::ItemFlags AdressBookModel::flags(const QModelIndex &index) const
{
	if (!index.isValid())
		return QAbstractTableModel::flags(index);

	if (index.column() == H_LABEL)
		return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
	else
		return QAbstractTableModel::flags(index);
}
AdressItem * AdressBookModel::item(int row)
{
	return m_lstItems.at(row);
}
void AdressBookModel::onAddItem()
{
	DlgAdress dlg(nullptr, dynamic_cast<QWidget *>(parent()));

	if (dlg.exec() == QDialog::Accepted)
	{
		addItem(new AdressItem(dlg.adress()));
		m_spAutoSaver->changeOccurred();
	}
}
void AdressBookModel::onEditItem(int row)
{
	AdressItem * p = m_lstItems.at(row);
	if (!p)
		return;

	DlgAdress dlg(p, dynamic_cast<QWidget *>(parent()));

	if (dlg.exec() == QDialog::Accepted)
	{
		QMutexLocker locker(&m_mtx);
		*m_lstItems.at(row) = dlg.adress();
		m_spAutoSaver->changeOccurred();
	}
}
void AdressBookModel::onDeleteItem(int row)
{
	QMessageBox mb(QMessageBox::Icon::Warning, tr("Warning"), tr("Delete this adress?")
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
void AdressBookModel::addItem(AdressItem * p)
{
	QMutexLocker locker(&m_mtx);

	int row = m_lstItems.count();
	beginInsertRows(QModelIndex(), row, row);
	m_lstItems.append(p);
	endInsertRows();
}
void AdressBookModel::load()
{
	QMutexLocker locker(&m_mtx);

	qDeleteAll(m_lstItems);
	m_lstItems.clear();

	QFile file(m_strFileName);
	if (file.open(QIODevice::ReadOnly))
	{
		QTextStream in(&file);
		QStringList row;
		bool bReadHeader = false;
		while (!in.atEnd())
		{
			QString line = in.readLine();
			if (Utils::parseCsvLine(line, row) && row.size() >= 2)
			{
				if (!bReadHeader && row[0] == "Label" && row[1] == "Adress")
				{ }
				else
					m_lstItems.append(new AdressItem(row[0], row[1]));
			}
			bReadHeader = true;
		}
		file.close();
	}
}
void AdressBookModel::save() const
{
	saveToFile(m_strFileName);
}
void AdressBookModel::exportToFile(const QString & filename) const
{
	saveToFile(filename);
}
void AdressBookModel::saveToFile(const QString & filename) const
{
	QMutexLocker locker(&m_mtx);

	QFile file(filename);
	if (file.open(QIODevice::WriteOnly))
	{
		QTextStream out(&file);
		QString line = QString("\"%1\",\"%2\"\n").arg("Label").arg("Adress");
		out << line;
		foreach (AdressItem * item, m_lstItems)
		{
			QString line = QString("\"%1\",\"%2\"\n").arg(item->label().replace("\"", "\"\"")).arg(item->adress().replace("\"", "\"\""));
			out << line;
		}
		file.close();
	}
}