#include "TxHashItem.h"

#include <QClipboard>

TxHashItem::TxHashItem(int ind, QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	ui.m_lLabel->setText(tr("%1. Tx Hash:").arg(ind));

	connect(ui.m_btnRemove, SIGNAL(clicked()), this, SIGNAL(removeMe()));
}

TxHashItem::~TxHashItem()
{
}

void TxHashItem::clear()
{
    ui.m_leLabel->setText("");
	ui.m_sbVoutPosition->setValue(0);
}
