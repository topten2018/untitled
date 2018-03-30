#include "DlgSettings.h"

DlgSettings::DlgSettings(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	connect(ui.m_btnOk, SIGNAL(clicked()), this, SLOT(save()));
}

DlgSettings::~DlgSettings()
{
}
void DlgSettings::load()
{

}
void DlgSettings::save()
{
	accept();
}
void DlgSettings::resetSettings()
{

}