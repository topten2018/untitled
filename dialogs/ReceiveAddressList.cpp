#include "ReceiveAddressList.h"

#include <QMenu>
#include <QFileDialog>
#include <QClipboard>

#include "models/AddressBookModel.h"


ReceiveAddressList::ReceiveAddressList(AddressBookModel * pModel, QWidget *parent)
	: QDialog(parent)
	, m_pModel(pModel)
{
    ui.setupUi(this);

	m_pContextMenu = new QMenu(this);
	m_pContextMenu->addAction(ui.m_actCopyLabel);
	m_pContextMenu->addAction(ui.m_actCopyAdress);
	m_pContextMenu->addSeparator();
	m_pContextMenu->addAction(ui.m_actEdit);
	   
	ui.m_tvAddressTable->setModel(m_pModel);

	int w = 600;
	ui.m_tvAddressTable->setColumnWidth(0, w / 2);
	ui.m_tvAddressTable->setColumnWidth(1, w / 2);

	connect(ui.m_btnAdd, SIGNAL(clicked()), this, SLOT(onAdd()));
	connect(ui.m_btnCopy, SIGNAL(clicked()), this, SLOT(onCopy()));
	connect(ui.m_btnExport, SIGNAL(clicked()), this, SLOT(onExport()));

	connect(ui.m_tvAddressTable, SIGNAL(clicked(QModelIndex)), this, SLOT(updateButtons()));
	connect(ui.m_tvAddressTable, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(updateButtons()));

	connect(ui.m_tvAddressTable, SIGNAL(customContextMenuRequested(const QPoint&)), SLOT(customMenuRequested(const QPoint&)));

	connect(ui.m_actCopyLabel, SIGNAL(triggered()), this, SLOT(onCopyLabel()));
	connect(ui.m_actCopyAdress, SIGNAL(triggered()), this, SLOT(onCopy()));
	connect(ui.m_actEdit, SIGNAL(triggered()), this, SLOT(onEdit()));

	updateButtons();
}
ReceiveAddressList::~ReceiveAddressList()
{
}
void ReceiveAddressList::updateButtons()
{
	QModelIndex ind = ui.m_tvAddressTable->currentIndex();
	bool bEnabled = ind.isValid();

	ui.m_btnCopy->setEnabled(bEnabled);
	ui.m_btnExport->setEnabled(m_pModel->rowCount() > 0);
}

void ReceiveAddressList::onAdd()
{
	m_pModel->onAddItem();
	updateButtons();
}

void ReceiveAddressList::onEdit()
{
	QModelIndex ind = ui.m_tvAddressTable->currentIndex();
	if (ind.isValid())
		m_pModel->onEditItem(ind.row());

	updateButtons();
}

void ReceiveAddressList::onCopy()
{
	QModelIndex ind = ui.m_tvAddressTable->currentIndex();
	if (ind.isValid())
	{
		QClipboard *clipboard = QApplication::clipboard();
		AddressItem * item = m_pModel->item(ind.row());
		if (item)
			clipboard->setText(item->address());
	}
}
void ReceiveAddressList::onCopyLabel()
{
	QModelIndex ind = ui.m_tvAddressTable->currentIndex();
	if (ind.isValid())
	{
		QClipboard *clipboard = QApplication::clipboard();
		AddressItem * item = m_pModel->item(ind.row());
		if (item)
			clipboard->setText(item->label());
	}
}

void ReceiveAddressList::onExport()
{
	QString file = QFileDialog::getSaveFileName(this,
		tr("Select file"),
		"./",
		tr("Csv files (*.csv)"));

	if (!file.isEmpty())
	{
		m_pModel->exportToFile(file);
	}
}

void ReceiveAddressList::customMenuRequested(const QPoint & pt)
{
	QModelIndex ind = ui.m_tvAddressTable->indexAt(pt);
	if (ind.isValid())
	{
		ui.m_tvAddressTable->setCurrentIndex(ind);
		m_pContextMenu->popup(ui.m_tvAddressTable->viewport()->mapToGlobal(pt));
	}
}