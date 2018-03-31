#include "DlgSettings.h"

#include <QSettings>
#include <QFile>

extern QString s_exeLocation;


DlgSettings::DlgSettings(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	ui.m_twMain->setCurrentIndex(0);

	connect(ui.m_cbUseProxy, SIGNAL(clicked()), this, SLOT(onUseProxy()));

	connect(ui.m_btnOk, SIGNAL(clicked()), this, SLOT(save()));
	connect(ui.m_btnResetSettings, SIGNAL(clicked()), this, SLOT(resetSettings()));

	load();
}

DlgSettings::~DlgSettings()
{
}
void DlgSettings::load()
{
	QSettings settings(s_exeLocation + tr("AprWallet.ini"), QSettings::IniFormat, this);

	settings.beginGroup("Main");
	ui.m_cbStartOnLogin->setChecked(settings.value("StartOnLogin", false).toBool());
	ui.m_sbDbSize->setValue(settings.value("bDbSize", 10).toInt());
	settings.endGroup();

	settings.beginGroup("Wallet");
	ui.m_cbCoinControl->setChecked(settings.value("CoinControl", false).toBool());
	ui.m_cbShowMasterNodesTab->setChecked(settings.value("ShowMasterNodesTab", false).toBool());
	ui.m_cbSpendUnconfirmedChange->setChecked(settings.value("SpendUnconfirmedChange", false).toBool());
	settings.endGroup();

	settings.beginGroup("Network");
	ui.m_cbMapPort->setChecked(settings.value("MapPort", false).toBool());
	ui.m_cbAllowIncomingConnections->setChecked(settings.value("AllowIncomingConnections", false).toBool());
	ui.m_cbUseProxy->setChecked(settings.value("UseProxy", false).toBool());
	QString proxy = settings.value("Proxy", "127.0.0.1:9050").toString();
	QStringList sl = proxy.split(":");
	ui.m_leProxyIp->setText(sl[0]);
	if (sl.count() > 1)
		ui.m_sbProxyPort->setValue(sl[1].toInt());
	else
		ui.m_sbProxyPort->setValue(9050);
	settings.endGroup();

	settings.beginGroup("Window");
	ui.m_cbMinimizeToTray->setChecked(settings.value("MinimizeToTray", false).toBool());
	ui.m_cbMinimizeOnClose->setChecked(settings.value("MinimizeOnClose", false).toBool());
	settings.endGroup();

	settings.beginGroup("Display");
	settings.endGroup();
}
void DlgSettings::save()
{
	QSettings settings(s_exeLocation + tr("AprWallet.ini"), QSettings::IniFormat, this);

	settings.beginGroup("Main");
	settings.setValue("StartOnLogin", ui.m_cbStartOnLogin->isChecked());
	settings.setValue("bDbSize", ui.m_sbDbSize->value());
	settings.endGroup();

	settings.beginGroup("Wallet");
	settings.setValue("CoinControl", ui.m_cbCoinControl->isChecked());
	settings.setValue("ShowMasterNodesTab", ui.m_cbShowMasterNodesTab->isChecked());
	settings.setValue("SpendUnconfirmedChange", ui.m_cbSpendUnconfirmedChange->isChecked());
	settings.endGroup();

	settings.beginGroup("Network");
	settings.setValue("MapPort", ui.m_cbMapPort->isChecked());
	settings.setValue("AllowIncomingConnections", ui.m_cbAllowIncomingConnections->isChecked());
	settings.setValue("UseProxy", ui.m_cbUseProxy->isChecked());
	settings.setValue("Proxy", QString("%1:%2").arg(ui.m_leProxyIp->text()).arg(ui.m_sbProxyPort->value()));
	settings.endGroup();

	settings.beginGroup("Window");
	settings.setValue("MinimizeToTray", ui.m_cbMinimizeToTray->isChecked());
	settings.setValue("MinimizeOnClose", ui.m_cbMinimizeOnClose->isChecked());
	settings.endGroup();

	settings.beginGroup("Display");
	settings.endGroup();

	accept();
}
void DlgSettings::resetSettings()
{
	ui.m_cbStartOnLogin->setChecked(false);
	ui.m_sbDbSize->setValue(10);
	
	ui.m_cbCoinControl->setChecked(false);
	ui.m_cbShowMasterNodesTab->setChecked(false);
	ui.m_cbSpendUnconfirmedChange->setChecked(false);
	
	ui.m_cbMapPort->setChecked(false);
	ui.m_cbAllowIncomingConnections->setChecked(false);
	ui.m_cbUseProxy->setChecked(false);
	ui.m_leProxyIp->setText("127.0.0.1");
	ui.m_sbProxyPort->setValue(9050);
	
	ui.m_cbMinimizeToTray->setChecked(false);
	ui.m_cbMinimizeOnClose->setChecked(false);	
}
void DlgSettings::onUseProxy()
{
	if (ui.m_cbUseProxy->isChecked())
	{
		ui.m_leProxyIp->setEnabled(true);
		ui.m_sbProxyPort->setEnabled(true);
	}
	else
	{
		ui.m_leProxyIp->setEnabled(false);
		ui.m_sbProxyPort->setEnabled(false);
	}
}