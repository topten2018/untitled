#include "ReceiveAddressInfo.h"
#include <QMessageBox>
#include <QClipboard>
#include <QFileDialog>
#include <QMenu>

ReceiveAddressInfo::ReceiveAddressInfo(const TransactionItem & ti, QWidget *parent)
	: QDialog(parent)
	, m_TransactionItem(ti)
{
    ui.setupUi(this);   

	ui.m_teInfo->setText(ti.info());
	m_QrCode.setText(ti.uri());

	setWindowTitle(tr("Request info to %1").arg(ti.label()));

	m_pImageMenu = new QMenu(this);
	m_pImageMenu->addAction(ui.m_actSaveImage);
	m_pImageMenu->addAction(ui.m_actCopyImage);

	ui.m_lQrCode->setPixmap(QPixmap::fromImage(m_QrCode.scaled(300, 300)));

	connect(ui.m_btnCopyUri, SIGNAL(clicked()), this, SLOT(onCopyUri()));
	connect(ui.m_btnCopyAddress, SIGNAL(clicked()), this, SLOT(onCopyAddress()));
	connect(ui.m_btnSaveImage, SIGNAL(clicked()), this, SLOT(onSaveImage()));

	connect(ui.m_actCopyImage, SIGNAL(triggered()), this, SLOT(onCopyImage()));
	connect(ui.m_actSaveImage, SIGNAL(triggered()), this, SLOT(onSaveImage()));

	connect(ui.m_lQrCode, SIGNAL(customContextMenuRequested(const QPoint&)), SLOT(showImageMenu(const QPoint&)));
}

ReceiveAddressInfo::~ReceiveAddressInfo()
{
}
void ReceiveAddressInfo::showImageMenu(const QPoint& pt)
{
	m_pImageMenu->popup(mapToGlobal(pt));
}

void ReceiveAddressInfo::onSaveImage()
{
	QString file = QFileDialog::getSaveFileName(this,
		tr("Select file"),
		"./",
		tr("Image files (*.png)"));

	if (!file.isEmpty())
	{
		m_QrCode.scaled(300, 300).save(file, "png");
	}
}
void ReceiveAddressInfo::onCopyImage()
{
	QClipboard *clipboard = QApplication::clipboard();
	clipboard->setImage(m_QrCode.scaled(300, 300));
}

void ReceiveAddressInfo::onCopyUri()
{
	QClipboard *clipboard = QApplication::clipboard();
	clipboard->setText(m_TransactionItem.uri());
}

void ReceiveAddressInfo::onCopyAddress()
{
    QClipboard *clipboard = QApplication::clipboard();
	clipboard->setText(m_TransactionItem.address());
}
