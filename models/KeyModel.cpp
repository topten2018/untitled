#include "KeyModel.h"

#include <QWidget>
#include <QListView>


KeyModel::KeyModel(QListView * p )
	: QAbstractListModel(p)
	, m_pListView(p)
{

	p->setModel(this);
	p->hide();
}

KeyModel::~KeyModel()
{
}
KeyItem * KeyModel::item(int i)
{
	return m_lstItems.at(i);
}
QVariant KeyModel::headerData(int , Qt::Orientation , int role) const
{
	QVariant result;

	if (role != Qt::DisplayRole)
		return result;
	
	return tr("RecPay");
}
QVariant KeyModel::data(const QModelIndex & index,int role) const
{
	if (!index.isValid() || !m_lstItems.count())
		return QVariant();
	
	KeyItem * item = m_lstItems.at(index.row());
	if (!item)
		return QVariant();

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
void KeyModel::addItem()
{
	KeyItem * item = new KeyItem(m_lstItems.count() + 1, m_pListView);

	connect(item, SIGNAL(removeMe()), this, SLOT(removeItem()));
	
	int row = m_lstItems.count();
	beginInsertRows(QModelIndex(), row, row);
	m_lstItems.append(item);
	endInsertRows();
	
	m_pListView->setIndexWidget(index(row, 0), item);
	m_pListView->show();
}
void KeyModel::clear()
{
	int count = m_lstItems.count();
	for (int i = count-1; i >= 0; --i)
	{
		KeyItem * item = m_lstItems.takeAt(i);
		if (item)
		{
			beginRemoveRows(QModelIndex(), i, i);
			item->deleteLater();
			endRemoveRows();
		}
	}

	if (!m_lstItems.count())
		m_pListView->hide();
}
void KeyModel::removeItem()
{
	KeyItem *item = qobject_cast<KeyItem*>(sender());
	int row = m_lstItems.indexOf(item);
	if (-1 == row)
		return;
	if (m_lstItems.count() > 0)
		removeRow(row);
	else
		item->clear();
}
bool KeyModel::removeRows(int row, int count, const QModelIndex &parent)
{
	if (parent.isValid())
		return false;

	int lastRow = row + count - 1;
	beginRemoveRows(parent, row, lastRow);
	for (int i = lastRow; i >= row; --i)
	{
		KeyItem * item = m_lstItems.takeAt(i);
		if (item)
		{			
			item->deleteLater();
		}
	}
	endRemoveRows();
	if (!m_lstItems.count())
		m_pListView->hide();
	return true;
}

