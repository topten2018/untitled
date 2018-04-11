#include "AddressKeyItem.h"

#include <QClipboard>

AddressKeyItem::AddressKeyItem(int ind, QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	ui.m_lLabel->setText(tr("Address / Key %1:").arg(ind));

	connect(ui.m_btnRemove, SIGNAL(clicked()), this, SIGNAL(removeMe()));
	connect(ui.m_btnPaste, SIGNAL(clicked()), this, SLOT(onPaste()));
}

AddressKeyItem::~AddressKeyItem()
{
}

void AddressKeyItem::clear()
{
    ui.m_leLabel->setText("");
}

void AddressKeyItem::onPaste()
{
	QClipboard *clipboard = QApplication::clipboard();
	ui.m_leLabel->setText(clipboard->text());
}
