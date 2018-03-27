#include "RecPayItem.h"

RecPayItem::RecPayItem(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	connect(ui.m_btnRemove, SIGNAL(clicked()), this, SIGNAL(removeMe()));
}

RecPayItem::~RecPayItem()
{
}

void RecPayItem::clear()
{
	ui.m_sbAmount->setValue(0);
	ui.m_leRecPay->setText("");
	ui.m_leLabel->setText("");
}