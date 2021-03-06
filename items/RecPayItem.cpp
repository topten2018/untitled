#include "RecPayItem.h"

#include <QClipboard>

RecPayItem::RecPayItem(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	connect(ui.m_btnRemove, SIGNAL(clicked()), this, SIGNAL(removeMe()));
	connect(ui.m_btnPaste, SIGNAL(clicked()), this, SLOT(onPaste()));
}

RecPayItem::~RecPayItem()
{
}

void RecPayItem::clear()
{
    ui.m_sbAmount->setValue(0.0);
	ui.m_leRecPay->setText("");
	ui.m_leLabel->setText("");
}

QString RecPayItem::sendto() const
{
    return ui.m_leRecPay->text();
}

double RecPayItem::amount() const
{
    return ui.m_sbAmount->value();
}


void RecPayItem::onPaste()
{
	QClipboard *clipboard = QApplication::clipboard();
	ui.m_leRecPay->setText(clipboard->text());
}

void RecPayItem::setUri(const QString & uri)
{
	ui.m_leRecPay->setText(uri);
}
