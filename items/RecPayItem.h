#ifndef RECPAYITEM_H
#define RECPAYITEM_H

#include <QWidget>
#include "ui_RecPayItem.h"

class RecPayItem : public QWidget
{
	Q_OBJECT

public:
	RecPayItem(QWidget *parent = Q_NULLPTR);
	~RecPayItem();

public slots:
	void clear();
signals:
	void removeMe();
private:
	Ui::RecPayItem ui;
};

#endif //RECPAYITEM_H