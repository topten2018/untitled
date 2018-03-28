#include "sendingaddresslist.h"
#include <QStandardItemModel>
#include <QStandardItem>
#include <QMessageBox>
#include <QMenu>
#include <QString>
#include <QFileDialog>
#include <QClipboard>

#include "models/AdressBookModel.h"

SendingAddressList::SendingAddressList(AdressBookModel * pModel, QWidget *parent)
	: QDialog(parent)
	, m_pModel(pModel)
{
    ui.setupUi(this);

	m_pContextMenu = new QMenu(this);
	m_pContextMenu->addAction(ui.m_actCopyLabel);
	m_pContextMenu->addAction(ui.m_actCopyAdress);
	m_pContextMenu->addSeparator();
	m_pContextMenu->addAction(ui.m_actEdit);

    ui.m_tvAdressTable->setModel(m_pModel);

	int w = 600;
	ui.m_tvAdressTable->setColumnWidth(0, w / 2);
	ui.m_tvAdressTable->setColumnWidth(1, w / 2);

	connect(ui.m_btnAdd, SIGNAL(clicked()), this, SLOT(onAdd()));
	connect(ui.m_btnDelete, SIGNAL(clicked()), this, SLOT(onDelete()));
	connect(ui.m_btnCopy, SIGNAL(clicked()), this, SLOT(onCopy()));
	connect(ui.m_btnExport, SIGNAL(clicked()), this, SLOT(onExport()));

	connect(ui.m_tvAdressTable, SIGNAL(clicked(QModelIndex)), this, SLOT(updateButtons()));
	connect(ui.m_tvAdressTable, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(updateButtons()));

	connect(ui.m_tvAdressTable, SIGNAL(customContextMenuRequested(const QPoint&)), SLOT(customMenuRequested(const QPoint&)));

	connect(ui.m_actCopyLabel, SIGNAL(triggered()), this, SLOT(onCopyLabel()));
	connect(ui.m_actCopyAdress, SIGNAL(triggered()), this, SLOT(onCopy()));
	connect(ui.m_actEdit, SIGNAL(triggered()), this, SLOT(onEdit()));
	
	updateButtons();
}

SendingAddressList::~SendingAddressList()
{
	delete m_pContextMenu;
}

void SendingAddressList::onAdd()
{
	m_pModel->onAddItem();
	updateButtons();
}

void SendingAddressList::onDelete()
{
	QModelIndex ind = ui.m_tvAdressTable->currentIndex();
	if (ind.isValid())
		m_pModel->onDeleteItem(ind.row());

	updateButtons();
}

void SendingAddressList::onEdit()
{
	QModelIndex ind = ui.m_tvAdressTable->currentIndex();
	if (ind.isValid())
		m_pModel->onEditItem(ind.row());

	updateButtons();
}

void SendingAddressList::onCopy()
{
	QModelIndex ind = ui.m_tvAdressTable->currentIndex();
	if (ind.isValid())
	{
		QClipboard *clipboard = QApplication::clipboard();
		AdressItem * item = m_pModel->item(ind.row());
		if (item)
			clipboard->setText(item->adress());
	}
}
void SendingAddressList::onCopyLabel()
{
	QModelIndex ind = ui.m_tvAdressTable->currentIndex();
	if (ind.isValid())
	{
		QClipboard *clipboard = QApplication::clipboard();
		AdressItem * item = m_pModel->item(ind.row());
		if (item)
			clipboard->setText(item->label());
	}
}

void SendingAddressList::updateButtons()
{
	QModelIndex ind = ui.m_tvAdressTable->currentIndex();
	bool bEnabled = ind.isValid();

	ui.m_btnDelete->setEnabled(bEnabled);
	ui.m_btnCopy->setEnabled(bEnabled);
	ui.m_btnExport->setEnabled(bEnabled);
}

void SendingAddressList::onExport()
{
	QString file = QFileDialog::getSaveFileName(this,
		tr("Select file"),
		"./",
		tr("Csv files (*.csv)"));

	if (!file.isEmpty())
	{
		m_pModel->exportToFile(file);
	}
	accept();
}

void SendingAddressList::customMenuRequested(const QPoint & pt)
{
	QModelIndex ind = ui.m_tvAdressTable->indexAt(pt);
	if (ind.isValid())
	{
		ui.m_tvAdressTable->setCurrentIndex(ind);
		m_pContextMenu->popup(ui.m_tvAdressTable->viewport()->mapToGlobal(pt));
	}
}