#ifndef ADDRESSITEM_H
#define ADDRESSITEM_H

#include <QWidget>

class AddressItem
{
	
public:
	AddressItem();
	AddressItem(const QString & label, const QString & address);
	~AddressItem();

	QString label() const;
	QString address() const;
public slots:
	void clear();
	void setLabel(const QString & label);
	void setAddress(const QString & address);
private:
	QString m_strLabel;
	QString m_strAddress;
};

#endif //ADDRESSITEM_H