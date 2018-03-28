#ifndef ADRESSBOOKMODEL_H
#define ADRESSBOOKMODEL_H

#include <QAbstractTableModel>
#include <QPointer>
#include <QMutex>

#include "Items/AdressItem.h"

class AutoSaver;

class AdressBookModel : public  QAbstractTableModel
{
	Q_OBJECT

public:
	AdressBookModel(const QString filename, QObject *parent);
	~AdressBookModel();

	enum HeaderNames 
	{ 
		H_LABEL = 0,
		H_ADRESS,
		H_COUNT
	};

	/// количество строк. Устанавливаем так, чтобы скроллер отображался корректно
	virtual int rowCount(const QModelIndex &) const override {return m_lstItems.size();};
	/// устанавливаем количество столбцов.
	virtual int columnCount(const QModelIndex &) const override {return H_COUNT;};
	/// функция для передачи данных пользователю
	virtual QVariant data(const QModelIndex &,int) const override;
	virtual bool setData(const QModelIndex &, const QVariant &, int) override;
	virtual Qt::ItemFlags flags(const QModelIndex &index) const override;
	virtual QVariant headerData( int section, Qt::Orientation orientation, int role) const override;

	AdressItem * item(int row);
public slots:
	void onAddItem();
	void onEditItem(int row);
	void onDeleteItem(int row);

	void load();
	void save() const;
	void exportToFile(const QString & filename) const;
private:
	void addItem(AdressItem *);
	void saveToFile(const QString & filename) const;

	QList<AdressItem*>		m_lstItems;
	QPointer<AutoSaver>		m_spAutoSaver;
	mutable QMutex			m_mtx;
	QString					m_strFileName;
};

#endif // ADRESSBOOKMODEL_H
