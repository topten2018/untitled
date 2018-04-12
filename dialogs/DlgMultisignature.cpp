#include "DlgMultisignature.h"

#include "models/AddressKeyModel.h"
#include "models/DestinationModel.h"
#include "models/TxHashModel.h"
#include "models/KeyModel.h"

DlgMultisignature::DlgMultisignature(Pages page, QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	m_pAddressModel = new AddressKeyModel(ui.m_lwAddressList);
	m_pDestinationModel = new DestinationModel(ui.m_lwAddressAmount);
	m_pTxHashModel = new TxHashModel(ui.m_lwHashList);
	m_pKeyModel = new KeyModel(ui.m_lwSignKeysList);

	connect(ui.m_btnAddAddress, SIGNAL(clicked()), this, SLOT(onAddAddress()));
	connect(ui.m_btnAddDestination, SIGNAL(clicked()), this, SLOT(onAddDestination()));
	connect(ui.m_btnAddRawInput, SIGNAL(clicked()), this, SLOT(onAddRawInput()));
	connect(ui.m_btnAddPrivateKey, SIGNAL(clicked()), this, SLOT(onAddPrivateKey()));
	
	ui.m_twMain->setCurrentIndex(page);
}

DlgMultisignature::~DlgMultisignature()
{
	delete m_pAddressModel;
	delete m_pDestinationModel;
	delete m_pTxHashModel;
	delete m_pKeyModel;
}

void DlgMultisignature::onAddAddress()
{
	m_pAddressModel->addItem();
}
void DlgMultisignature::onAddDestination()
{
	m_pDestinationModel->addItem();
}
void DlgMultisignature::onAddRawInput()
{
	m_pTxHashModel->addItem();
}
void DlgMultisignature::onAddPrivateKey()
{
	m_pKeyModel->addItem();
}
void DlgMultisignature::updateButtons()
{
	ui.m_lwAddressAmount->setVisible(m_pDestinationModel->rowCount());
}
