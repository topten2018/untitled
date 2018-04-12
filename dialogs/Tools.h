#ifndef TOOLS_H
#define TOOLS_H

#include <QDialog>
#include "ui_Tools.h"

class Tools : public QDialog
{
    Q_OBJECT
    
public:

	enum Pages
	{
		InformationPage = 0,
		ConsolePage,
		NetworkPage,
		PeersPage,
		WalletRepair
	};

	Tools(QWidget *parent = 0);
    ~Tools();
	
public slots:
	void show(Pages page);   

private slots:
    void onSend();

private:
    Ui::Tools ui;
};

#endif // TOOLS_H
