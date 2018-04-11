#ifndef KEY_ITEM_H
#define KEY_ITEM_H

#include <QWidget>
#include "ui_KeyItem.h"

class KeyItem : public QWidget
{
	Q_OBJECT

public:
	KeyItem(int ind, QWidget *parent = Q_NULLPTR);
	~KeyItem();

public slots:
	void clear();
signals:
	void removeMe();
private:
	Ui::KeyItem ui;
};

#endif //KEY_ITEM_H
