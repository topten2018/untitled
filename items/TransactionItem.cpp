#include "TransactionItem.h"

#include <QClipboard>

TransactionItem::TransactionItem()
{

}
TransactionItem::TransactionItem(const TransactionItem & ti)
	: m_dtDate(ti.m_dtDate)
	, m_strLabel(ti.m_strLabel)
	, m_strAddress(ti.m_strAddress)
	, m_strMessage(ti.m_strMessage)
	, m_strCoin(ti.m_strCoin)
	, m_strAmount(ti.m_strAmount)
{

}
TransactionItem::TransactionItem(TransactionItem && ti)
	: m_dtDate(ti.m_dtDate)
	, m_strLabel(ti.m_strLabel)
	, m_strAddress(ti.m_strAddress)
	, m_strMessage(ti.m_strMessage)
	, m_strCoin(ti.m_strCoin)
	, m_strAmount(ti.m_strAmount)
{

}

TransactionItem::~TransactionItem()
{

}
QDateTime TransactionItem::date() const
{
	return m_dtDate;
}
QString TransactionItem::label() const
{
	return m_strLabel;
}
QString TransactionItem::address() const
{
	return m_strAddress;
}
QString TransactionItem::message() const
{
	return m_strMessage;
}
QString TransactionItem::coin() const
{
	return m_strCoin;
}
QString TransactionItem::amount() const
{
	return m_strAmount;
}

void TransactionItem::setDate(const QDateTime& dt) 
{
	m_dtDate = dt;
}
void TransactionItem::setLabel(const QString& label) 
{
	m_strLabel = label;
}
void TransactionItem::setAddress(const QString& address) 
{
	m_strAddress = address;
}
void TransactionItem::setMessage(const QString& message) 
{
	m_strMessage = message;
}
void TransactionItem::setCoin(const QString& coin) 
{
	m_strCoin = coin;
}
void TransactionItem::setAmount(const QString& d)
{
	m_strAmount = d;
}

QString TransactionItem::info() const
{
	QString res = tr("<b>Payment information</b><br/>");
	res += tr("<b>URI:</b> %1<br/>").arg(m_strAddress);
	res += tr("<b>Address:</b> %1<br/>").arg(m_strAddress);
	if (!m_strAmount.isEmpty())
		res += tr("<b>Amount:</b> %1 %2<br/>").arg(m_strAmount).arg(m_strCoin);
	if (!m_strLabel.isEmpty())
		res += tr("<b>Label:</b> %1<br/>").arg(m_strLabel);
	if (!m_strMessage.isEmpty())
		res += tr("<b>Message:</b> %1").arg(m_strMessage);
	return res;
}
QString TransactionItem::uri() const
{
	return m_strAddress;
}