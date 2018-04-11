#ifndef ADDRESS_KEY_ITEM_H
#define ADDRESS_KEY_ITEM_H

#include <QWidget>
#include "ui_AddressKeyItem.h"

class AddressKeyItem : public QWidget
{
	Q_OBJECT

public:
	AddressKeyItem(int ind, QWidget *parent = Q_NULLPTR);
	~AddressKeyItem();

public slots:
	void clear();
	void onPaste();
signals:
	void removeMe();
private:
	Ui::AddressKeyItem ui;
};

#endif //ADDRESS_KEY_ITEM_H
