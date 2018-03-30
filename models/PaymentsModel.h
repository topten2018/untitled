#ifndef PAYMENTMODEL_H
#define PAYMENTMODEL_H

#include <QAbstractTableModel>
#include <QPointer>
#include <QMutex>

#include "Items/TransactionItem.h"

class AutoSaver;

class PaymentsModel : public  QAbstractTableModel
{
	Q_OBJECT

public:
	PaymentsModel(const QString filename, QObject *parent);
	~PaymentsModel();

	enum HeaderNames 
	{ 
		H_DATE = 0,
		H_LABEL,
		H_MESSAGE,
		H_AMOUNT,
		H_COUNT
	};

	/// количество строк. Устанавливаем так, чтобы скроллер отображался корректно
	virtual int rowCount(const QModelIndex & = QModelIndex()) const override {return m_lstItems.size();};
	/// устанавливаем количество столбцов.
	virtual int columnCount(const QModelIndex &) const override {return H_COUNT;};
	/// функция для передачи данных пользователю
	virtual QVariant data(const QModelIndex &,int) const override;
	virtual QVariant headerData( int section, Qt::Orientation orientation, int role) const override;

	TransactionItem * item(int row);
	void append(TransactionItem *);
public slots:
	void onAddItem();
	void onEditItem(int row);
	void onDeleteItem(int row);

	void load();
	void save() const;
	void exportToFile(const QString & filename) const;
private:
	void addItem(TransactionItem *);
	void saveToFile(const QString & filename, bool bWriteHeader) const;
	QList<TransactionItem*>	m_lstItems;
	QPointer<AutoSaver>		m_spAutoSaver;
	mutable QMutex			m_mtx;
	QString					m_strFileName;
};

#endif // PAYMENTMODEL_H
