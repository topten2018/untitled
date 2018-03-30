#ifndef TRANSACTIONINFO_H
#define TRANSACTIONINFO_H

#include <QString>
#include <QDateTime>
#include <QObject>

class TransactionItem : public QObject
{
	Q_OBJECT

public:
	TransactionItem();
	TransactionItem(const TransactionItem & );
	TransactionItem(TransactionItem &&);
	~TransactionItem();

	QDateTime date() const;
	QString label() const;
	QString address() const;
	QString message() const;
	QString coin() const;
	QString amount() const;

	void setDate(const QDateTime& dt);
	void setLabel(const QString& label);
	void setAddress(const QString& address);
	void setMessage(const QString& msg);
	void setCoin(const QString& coin);
	void setAmount(const QString& d);

	QString info() const;
	QString uri() const;
private:
	QDateTime	m_dtDate;
	QString		m_strLabel;
	QString		m_strAddress;
	QString		m_strMessage;
	QString		m_strCoin;
	QString		m_strAmount;
};

#endif //TRANSACTIONINFO_H