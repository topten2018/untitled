#include "DestinationModel.h"

#include <QWidget>
#include <QListView>


DestinationModel::DestinationModel(QListView * p )
	: QAbstractListModel(p)
	, m_pListView(p)
{

	p->setModel(this);
	addItem();
}

DestinationModel::~DestinationModel()
{
}
DestinationItem * DestinationModel::item(int i)
{
	return m_lstItems.at(i);
}
QVariant DestinationModel::headerData(int , Qt::Orientation , int role) const
{
	QVariant result;

	if (role != Qt::DisplayRole)
		return result;
	
	return tr("RecPay");
}
QVariant DestinationModel::data(const QModelIndex & index,int role) const
{
	if (!index.isValid())
		return QVariant();

	DestinationItem * item = m_lstItems.at(index.row());

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
void DestinationModel::addItem()
{
	DestinationItem * item = new DestinationItem(m_lstItems.count() + 1, m_pListView);

	connect(item, SIGNAL(removeMe()), this, SLOT(removeItem()));
	
	int row = m_lstItems.count();
	beginInsertRows(QModelIndex(), row, row);
	m_lstItems.append(item);
	endInsertRows();
	
	m_pListView->setIndexWidget(index(row, 0), item);
}
void DestinationModel::clear()
{
	int count = m_lstItems.count();
	for (int i = count-1; i >= 1; --i)
	{
		DestinationItem * item = m_lstItems.takeAt(i);
		if (item)
		{
			beginRemoveRows(QModelIndex(), i, i);
			item->deleteLater();
			endRemoveRows();
		}
	}
	DestinationItem * item = m_lstItems.at(0);
	if (item)
		item->clear();
}
void DestinationModel::removeItem()
{
	DestinationItem *item = qobject_cast<DestinationItem*>(sender());
	int row = m_lstItems.indexOf(item);
	if (-1 == row)
		return;
	if (m_lstItems.count() > 1)
		removeRow(row);
	else
		item->clear();
}
bool DestinationModel::removeRows(int row, int count, const QModelIndex &parent)
{
	if (parent.isValid())
		return false;

	int lastRow = row + count - 1;
	beginRemoveRows(parent, row, lastRow);
	for (int i = lastRow; i >= row; --i)
	{
		if (m_lstItems.count() <= 1)
		{
			m_lstItems.at(0)->clear();
			endRemoveRows();
			return true;
		}
		DestinationItem * item = m_lstItems.takeAt(i);
		if (item)
		{			
			item->deleteLater();
		}
	}
	endRemoveRows();
	return true;
}

