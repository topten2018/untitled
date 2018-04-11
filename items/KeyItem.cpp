#include "KeyItem.h"

#include <QClipboard>

KeyItem::KeyItem(int ind, QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	ui.m_lLabel->setText(tr("Key %1:").arg(ind));

	connect(ui.m_btnRemove, SIGNAL(clicked()), this, SIGNAL(removeMe()));
}

KeyItem::~KeyItem()
{
}

void KeyItem::clear()
{
    ui.m_leKey->setText("");
}
