#include "DestinationItem.h"

#include <QClipboard>

DestinationItem::DestinationItem(int ind, QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	ui.m_lLabel->setText(tr("%1. Address:").arg(ind));

	connect(ui.m_btnRemove, SIGNAL(clicked()), this, SIGNAL(removeMe()));
}

DestinationItem::~DestinationItem()
{
}

void DestinationItem::clear()
{
    ui.m_leLabel->setText("");
	ui.m_sbAmount->setValue(0);
}
