#include "DlgAdress.h"

DlgAdress::DlgAdress(const AdressItem * p, QWidget *parent)
	: QDialog(parent)	 
{
	ui.setupUi(this);

	if (p)
	{
		m_Adress = *p;
		setWindowTitle(tr("Adress"));

		ui.m_leLabel->setText(p->label());
		ui.m_leAdress->setText(p->adress());
	}
	else
		setWindowTitle(tr("New adress"));
}

DlgAdress::~DlgAdress()
{
}

AdressItem DlgAdress::adress() 
{
	m_Adress.setLabel(ui.m_leLabel->text());
	m_Adress.setAdress(ui.m_leAdress->text());
	return m_Adress;
}
