#ifndef ADRESSITEM_H
#define ADRESSITEM_H

#include <QWidget>

class AdressItem
{
	
public:
	AdressItem();
	AdressItem(const QString & label, const QString & adress);
	~AdressItem();

	QString label() const;
	QString adress() const;
public slots:
	void clear();
	void setLabel(const QString & label);
	void setAdress(const QString & adress);
private:
	QString m_strLabel;
	QString m_strAdress;
};

#endif //ADRESSITEM_H