#include "models/PaymentsModel.h"

#include "Utils/AutoSaver.h"
#include "Utils/StringUtils.h"

#include "dialogs/DlgAddress.h"

#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QMutexLocker>

PaymentsModel::PaymentsModel(const QString filename, QObject *parent)
	: QAbstractTableModel(parent)
	, m_strFileName(filename)
	, m_mtx(QMutex::Recursive)
{
	m_spAutoSaver = new AutoSaver(this);
	load();
}

PaymentsModel::~PaymentsModel()
{
	m_spAutoSaver->saveIfNeccessary();
	qDeleteAll(m_lstItems);
}
QVariant PaymentsModel::headerData(int section, Qt::Orientation , int role) const
{
	QVariant result;

	switch (role)
	{
	case Qt::SizeHintRole:
		switch (section)
		{
		case H_DATE:
			return QSize(100, 28);
			break;
		case H_LABEL:
			return QSize(220, 28);
			break;
		case H_AMOUNT:
			return QSize(150, 28);
			break;
		}
		break;
	case Qt::DisplayRole:
		switch (section)
		{
		case H_DATE:
			result = tr("Date");
			break;
		case H_LABEL:
			result = tr("Label");
			break;
		case H_MESSAGE:
			result = tr("Message");
			break;
		case H_AMOUNT:
			result = tr("Amount (APR)");
			break;
		};
		break;
	}
	return result;
}

QVariant PaymentsModel::data(const QModelIndex & index,int role) const
{
	if (!index.isValid())
		return QVariant();

	const TransactionItem * item = m_lstItems.at(index.row());

	switch (role)
	{
	case Qt::TextAlignmentRole:
		if (index.column() == H_AMOUNT)
		{
			return Qt::AlignRight + Qt::AlignVCenter;
		}
		break;
	case Qt::DisplayRole:
	{
		switch (index.column())
		{
		case H_DATE:
			return item->date().toString("dd.MM.yyyy hh:mm");
			break;
		case H_LABEL:
			return item->label();
			break;
		case H_MESSAGE:
			return item->message();
			break;		
		case H_AMOUNT:
			return item->amount();
			break;
		};
		break;
	}	
	}
	return QVariant();
}

TransactionItem * PaymentsModel::item(int row)
{
	return m_lstItems.at(row);
}
void PaymentsModel::onAddItem()
{
/*	DlgAddress dlg(nullptr, dynamic_cast<QWidget *>(parent()));

	if (dlg.exec() == QDialog::Accepted)
	{
		addItem(new TransactionItem(dlg.address()));
		m_spAutoSaver->changeOccurred();
	}*/
}
void PaymentsModel::append(TransactionItem * p)
{
	addItem(p);
	m_spAutoSaver->changeOccurred();
}
void PaymentsModel::onEditItem(int row)
{
	TransactionItem * p = m_lstItems.at(row);
	if (!p)
		return;

/*	DlgAddress dlg(p, dynamic_cast<QWidget *>(parent()));

	if (dlg.exec() == QDialog::Accepted)
	{
		QMutexLocker locker(&m_mtx);
		*m_lstItems.at(row) = dlg.address();
		m_spAutoSaver->changeOccurred();
	}*/
}
void PaymentsModel::onDeleteItem(int row)
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
void PaymentsModel::addItem(TransactionItem * p)
{
	QMutexLocker locker(&m_mtx);
	beginInsertRows(QModelIndex(), 0, 0);
	m_lstItems.insert(0, p);
	endInsertRows();
}
void PaymentsModel::load()
{
	QMutexLocker locker(&m_mtx);

/*	qDeleteAll(m_lstItems);
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
	}*/
}
void PaymentsModel::save() const
{
	saveToFile(m_strFileName, false);
}
void PaymentsModel::exportToFile(const QString & filename) const
{
	saveToFile(filename, true);
}
void PaymentsModel::saveToFile(const QString & filename, bool bWriteHeader) const
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
		foreach (TransactionItem * item, m_lstItems)
		{
			QString line = QString("\"%1\",\"%2\"\r\n").arg(item->label().replace("\"", "\"\"")).arg(item->address().replace("\"", "\"\""));
			out << line;
		}
		file.close();
	}
}