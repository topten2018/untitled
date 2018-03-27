#ifndef RECPAY_MODEL_H
#define RECPAY_MODEL_H

#include <QAbstractListModel>

#include "Items/RecPayItem.h"

class QListView;

class RecPayModel : public QAbstractListModel
{
	Q_OBJECT

public:
	RecPayModel(QListView * p);
	~RecPayModel();

	/*
	bool updateItem(zPatientItem *);
	bool deleteItem(int row);
	*/
	/// количество строк. Устанавливаем так, чтобы скроллер отображался корректно
	virtual int rowCount(const QModelIndex &) const override {return m_lstItems.size();};
	/// устанавливаем количество столбцов.
	virtual int columnCount(const QModelIndex &) const override {return 1;};
	/// функция для передачи данных пользователю
	virtual QVariant data(const QModelIndex &,int) const override;
	//virtual bool setData(const QModelIndex &, const QVariant &, int);
	virtual bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

	virtual QVariant headerData( int section, Qt::Orientation orientation, int role) const override;

	RecPayItem * item(int i);
public slots:
	void addItem();
	void clear();
private slots:
	void removeItem();
private:
	QList<RecPayItem*>	m_lstItems;
	QListView *			m_pListView;
};

#endif // RECPAY_MODEL_H
