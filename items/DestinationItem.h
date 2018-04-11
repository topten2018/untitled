#ifndef DESTINATION_ITEM_H
#define DESTINATION_ITEM_H

#include <QWidget>
#include "ui_DestinationItem.h"

class DestinationItem : public QWidget
{
	Q_OBJECT

public:
	DestinationItem(int ind, QWidget *parent = Q_NULLPTR);
	~DestinationItem();

public slots:
	void clear();
signals:
	void removeMe();
private:
	Ui::DestinationItem ui;
};

#endif //DESTINATION_ITEM_H
