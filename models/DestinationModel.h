#ifndef DESTINATION_MODEL_H
#define DESTINATION_MODEL_H

#include <QAbstractListModel>

#include "Items/DestinationItem.h"

class QListView;

class DestinationModel : public QAbstractListModel
{
	Q_OBJECT

public:
	DestinationModel(QListView * p);
	~DestinationModel();

	/*
	bool updateItem(zPatientItem *);
	bool deleteItem(int row);
	*/
	/// ���������� �����. ������������� ���, ����� �������� ����������� ���������
	virtual int rowCount(const QModelIndex & = QModelIndex()) const override {return m_lstItems.size();};
	/// ������������� ���������� ��������.
	virtual int columnCount(const QModelIndex &) const override {return 1;};
	/// ������� ��� �������� ������ ������������
	virtual QVariant data(const QModelIndex &,int) const override;
	//virtual bool setData(const QModelIndex &, const QVariant &, int);
	virtual bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

	virtual QVariant headerData( int section, Qt::Orientation orientation, int role) const override;

	DestinationItem * item(int i);
public slots:
	void addItem();
	void clear();
private slots:
	void removeItem();
private:
	QList<DestinationItem*>	m_lstItems;
	QListView *				m_pListView;
};

#endif // DESTINATION_MODEL_H
