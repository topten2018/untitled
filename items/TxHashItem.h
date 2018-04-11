#ifndef TXHASH_ITEM_H
#define TXHASH_ITEM_H

#include <QWidget>
#include "ui_TxHashItem.h"

class TxHashItem : public QWidget
{
	Q_OBJECT

public:
	TxHashItem(int ind, QWidget *parent = Q_NULLPTR);
	~TxHashItem();

public slots:
	void clear();
signals:
	void removeMe();
private:
	Ui::TxHashItem ui;
};

#endif //TXHASH_ITEM_H
