#include "AddressItem.h"

AddressItem::AddressItem()
{
}
AddressItem::AddressItem(const QString & label, const QString & address)
	: m_strLabel(label)
	, m_strAddress(address)
{

}
AddressItem::~AddressItem()
{
}

void AddressItem::clear()
{
	m_strAddress = "";
	m_strLabel = "";
}
QString AddressItem::label() const
{
	return m_strLabel;
}
QString AddressItem::address() const
{
	return m_strAddress;
}
void AddressItem::setLabel(const QString & label)
{
	m_strLabel = label;
}
void AddressItem::setAddress(const QString & address)
{
	m_strAddress = address;
}