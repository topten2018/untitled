#include "AdressItem.h"

AdressItem::AdressItem()
{
}
AdressItem::AdressItem(const QString & label, const QString & adress)
	: m_strLabel(label)
	, m_strAdress(adress)
{

}
AdressItem::~AdressItem()
{
}

void AdressItem::clear()
{
	m_strAdress = "";
	m_strLabel = "";
}
QString AdressItem::label() const
{
	return m_strLabel;
}
QString AdressItem::adress() const
{
	return m_strAdress;
}
void AdressItem::setLabel(const QString & label)
{
	m_strLabel = label;
}
void AdressItem::setAdress(const QString & adress)
{
	m_strAdress = adress;
}