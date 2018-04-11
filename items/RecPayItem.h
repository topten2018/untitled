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
   QString sendto() const;
   double amount() const;

public slots:
	void clear();
	void onPaste();
	void setUri(const QString & uri);
signals:
	void removeMe();
private:
	Ui::RecPayItem ui;
};

#endif //RECPAYITEM_H
