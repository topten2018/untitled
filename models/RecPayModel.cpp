#include "RecPayModel.h"

#include <QWidget>
#include <QListView>


RecPayModel::RecPayModel(QListView * p )
	: QAbstractListModel(p)
	, m_pListView(p)
{

	p->setModel(this);
	addItem();
}

RecPayModel::~RecPayModel()
{
}
RecPayItem * RecPayModel::item(int i)
{
	return m_lstItems.at(i);
}
QVariant RecPayModel::headerData(int , Qt::Orientation , int role) const
{
	QVariant result;

	if (role != Qt::DisplayRole)
		return result;
	
	return tr("RecPay");
}
QVariant RecPayModel::data(const QModelIndex & index,int role) const
{
	if (!index.isValid())
		return QVariant();

	RecPayItem * item = m_lstItems.at(index.row());

	switch (role)
	{
	case Qt::SizeHintRole:
		return item->sizeHint();
		break;
	default:
		break;
	}

	return QVariant();
}
void RecPayModel::addItem()
{
	RecPayItem * item = new RecPayItem(m_pListView);

	connect(item, SIGNAL(removeMe()), this, SLOT(removeItem()));
	
	int row = m_lstItems.count();
	beginInsertRows(QModelIndex(), row, row);
	m_lstItems.append(item);
	endInsertRows();
	
	m_pListView->setIndexWidget(index(row, 0), item);
}
void RecPayModel::clear()
{
	int count = m_lstItems.count();
	for (int i = count; i >= 1; --i)
	{
		RecPayItem * item = m_lstItems.takeAt(i);
		if (item)
		{
			beginRemoveRows(QModelIndex(), i, i);
			item->deleteLater();
			endRemoveRows();
		}
	}
	RecPayItem * item = m_lstItems.at(0);
	if (item)
		item->clear();
}
void RecPayModel::removeItem()
{
	RecPayItem *item = qobject_cast<RecPayItem*>(sender());
	int row = m_lstItems.indexOf(item);
	if (-1 == row)
		return;
	if (m_lstItems.count() > 1)
		removeRow(row);
	else
		item->clear();
}
bool RecPayModel::removeRows(int row, int count, const QModelIndex &parent)
{
	if (parent.isValid())
		return false;

	int lastRow = row + count - 1;
	for (int i = lastRow; i >= row; --i)
	{
		if (m_lstItems.count() <= 1)
		{
			m_lstItems.at(0)->clear();
			return true;
		}
		RecPayItem * item = m_lstItems.takeAt(i);
		if (item)
		{		
			beginRemoveRows(parent, i, i);
			item->deleteLater();
			endRemoveRows();
		}
	}
	return true;
}


/*
void zPatientModel::insert(zPatientItem *pItem)
{
	int row = m_lstItems.count();
	
	beginInsertRows(QModelIndex(), row, row);
	m_lstItems.append(pItem);
	endInsertRows();
}


bool zPatientModel::updateItem(zPatientItem *pItem)
{
	if (!pItem)
		return false;

	QMutexLocker lock(m_pMtx);

	QSqlQuery qUpdate;
	
	if (!qUpdate.prepare("UPDATE Patient SET doctor_id=:doctor_id, family_name=:family_name, "
		"first_name=:first_name, second_name=:second_name, "
		"sex=:sex, date_birth=:date_birth, active=:active, description=:description  WHERE id=:id;"))
	{
		qDebug() << tr("Error save info for patient [%1]").arg(qUpdate.lastError().text());
		return false;
	}


	if (!pItem->m_bChanged)
		return false;

	pItem->m_bChanged = false;

	qUpdate.bindValue(":id", pItem->m_uiId);
	qUpdate.bindValue(":doctor_id", m_uiDoctorId);
	qUpdate.bindValue(":family_name", pItem->m_strFamilyName);
	qUpdate.bindValue(":first_name", pItem->m_strFirstName);
	qUpdate.bindValue(":second_name", pItem->m_strSecondName);
	qUpdate.bindValue(":sex", pItem->m_chSex == 'W' ? "W" : "M");
	qUpdate.bindValue(":date_birth", pItem->m_dtBirthday);
	qUpdate.bindValue(":active", pItem->m_chActive == 'N' ? "N" : "Y");
	qUpdate.bindValue(":description", pItem->m_strDescription);

	if (!qUpdate.exec())
	{
		qDebug() << tr("Error save info for patient [%1]").arg(qUpdate.lastError().text());
		return false;
	}
	beginResetModel();
	endResetModel();
	
	return true;
}
bool zPatientModel::deleteItem(int row)
{
	QMutexLocker lock(m_pMtx);
	QSqlQuery qDelete;
	if (!qDelete.prepare("UPDATE Patient SET active='N' WHERE id=:id;"))
		return false;

	zPatientItem * item = m_lstItems.at(row);
	if (!item)
		return false;

	qDelete.bindValue(":id", item->m_uiId);
	if (!qDelete.exec())
	{
		qDebug() << tr("Error delete patient [%1]").arg(qDelete.lastError().text());
	}
	beginRemoveRows(QModelIndex(), row, row);
	m_lstItems.removeAt(row);
	delete item;
	endRemoveRows();
	return true;
}

void zPatientModel::setDoctorId(quint32 uiDoctorId)
{
	m_uiDoctorId = uiDoctorId;
	load();
}

bool zPatientModel::load()
{
	QMutexLocker lock(m_pMtx);


	qDeleteAll(m_lstItems);
	m_lstItems.clear();

	QSqlQuery q;

	QString str = "SELECT id, family_name, first_name, second_name, sex, date_birth, active, description "
		"FROM Patient "
		"WHERE active='Y' AND doctor_id=:doctor_id "
		"ORDER BY family_name, first_name, second_name;";

	if (!q.prepare(str))
	{
		qDebug() << tr("Error get patients [%1]").arg(q.lastError().text());
		return false;
	}

	q.bindValue(":doctor_id", m_uiDoctorId);

	if (!q.exec())
	{
		qDebug() << tr("Error get patients [%1]").arg(q.lastError().text());
		return false;
	}
	
	while (q.next())
	{
		zPatientItem item;
		item.m_uiId			= q.value(0).toUInt();
		item.m_strFamilyName= q.value(1).toString();
		item.m_strFirstName = q.value(2).toString();
		item.m_strSecondName= q.value(3).toString();
		if (q.value(4).toString() == "W")
			item.m_chSex = 'W';
		else
			item.m_chSex = 'M';
		item.m_dtBirthday	= q.value(5).toDate();
        if (q.value(6).toString() == "N")
			item.m_chActive	= 'N';
		else
			item.m_chActive = 'Y';
		item.m_strDescription=q.value(7).toString();

		insert(new zPatientItem(std::move(item)));
	}

	return true;
}
/*
bool zPatientModel::save() const
{
	QMutexLocker lock(m_pMtx);

	QSqlQuery qUpdate, qIns, *q;
	if (!qIns.prepare("INSERT INTO Patient(doctor_id, family_name, first_name, second_name, "
		"sex, date_birth, active, description) "
		"VALUES (:doctor_id, :family_name, :first_name, :second_name, "
		":sex, :date_birth, :active, :description) ;"))
	{
		qDebug() << tr("Error save info for patient [%1]").arg(qIns.lastError().text());
		return false;
	}

	if (!qUpdate.prepare("UPDATE Patient SET doctor_id=:doctor_id, family_name=:family_name, "
		"first_name=:first_name, second_name=:second_name, "
		"sex=:sex, date_birth=:date_birth, active=:active, description=:description  WHERE id=:id;"))
	{
		qDebug() << tr("Error save info for patient [%1]").arg(qUpdate.lastError().text());
		return false;
	}
	
	for (int i = 0; i < m_lstItems.size(); ++i)
	{
		zPatientItem * pItem = m_lstItems.at(i);
		if (!pItem)
			continue;

		if (!pItem->m_bChanged)
			continue;

		if (!pItem->m_uiId)
			q = &qIns;			
		else
			q = &qUpdate;
		
		q->bindValue(":id",			pItem->m_uiId);
		q->bindValue(":doctor_id",  m_uiDoctorId);
		q->bindValue(":family_name",pItem->m_strFamilyName);
		q->bindValue(":first_name", pItem->m_strFirstName);
		q->bindValue(":second_name",pItem->m_strSecondName);
		q->bindValue(":sex",		pItem->m_chSex=='W' ? "W" : "M");
		q->bindValue(":date_birth", pItem->m_dtBirthday);
		q->bindValue(":active",		pItem->m_chActive == 'N' ? "N" : "Y");
		q->bindValue(":description",pItem->m_strDescription);

		if (!q->exec())
		{
			qDebug() << tr("Error save info for patient [%1]").arg(q->lastError().text());
			return false;
		}
		if (!pItem->m_uiId)
		{
			QSqlQuery q;
			if (q.exec("SELECT last_insert_rowid();"))
			{
				if (q.next())
					pItem->m_uiId = q.value(0).toInt();
			}
			else
			{
				qDebug() << tr("Error save info for patient [%1]").arg(q.lastError().text());
				return false;
			}
		}
	}

	return true;
}*/

