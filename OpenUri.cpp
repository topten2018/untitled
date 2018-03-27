#include "OpenUri.h"

#include <QUrl>
#include <QFileDialog>

OpenUri::OpenUri(QWidget *parent) 
	: QDialog(parent)
{
    ui.setupUi(this);

	updateButtons();

	connect(ui.m_btnBrowse, SIGNAL(clicked()), this, SLOT(onBrowse()));
	connect(ui.m_leUri, SIGNAL(textChanged(QString)), this, SLOT(updateButtons()));
}

OpenUri::~OpenUri()
{
}
void OpenUri::onBrowse()
{
	QString file = QFileDialog::getOpenFileName(this,
		tr("Select file"),
		"./",
		tr("All files (*.*)"));

	if (!file.isEmpty())
	{
		ui.m_leUri->setText(QUrl::toPercentEncoding(file));
	}
}
QString OpenUri::uri() const
{
	return ui.m_leUri->text();
}
void OpenUri::updateButtons()
{
	ui.m_btnOk->setEnabled(!ui.m_leUri->text().isEmpty());
}