#include "DlgAddress.h"

DlgAddress::DlgAddress(const AddressItem * p, QWidget *parent)
	: QDialog(parent)	 
{
	ui.setupUi(this);

	if (p)
	{
		m_Address = *p;
		setWindowTitle(tr("Address"));

		ui.m_leLabel->setText(p->label());
		ui.m_leAddress->setText(p->address());
	}
	else
		setWindowTitle(tr("New address"));
}

DlgAddress::~DlgAddress()
{
}

AddressItem DlgAddress::address() 
{
	m_Address.setLabel(ui.m_leLabel->text());
	m_Address.setAddress(ui.m_leAddress->text());
	return m_Address;
}
