#ifndef DLGBLOCKCHAIN_H
#define DLGBLOCKCHAIN_H

#include <QDialog>
#include "ui_DlgBlockchainExplorer.h"

class DlgBlockchainExplorer : public QDialog
{
	Q_OBJECT

public:
	DlgBlockchainExplorer(QWidget *parent = Q_NULLPTR);
	~DlgBlockchainExplorer();

protected:
	void keyPressEvent(QKeyEvent* event);
	void showEvent(QShowEvent*);

private slots:
	void onSearch();
	void goTo(const QString& query);
	void back();
	void forward();
private:
	Ui::DlgBlockchainExplorer ui;

	bool m_NeverShown;
	int m_HistoryIndex;
	QStringList m_History;

//	void setBlock(CBlockIndex* pBlock);
	bool switchTo(const QString& query);
	void setContent(const std::string& content);
	void updateNavButtons();
};

#endif // DLGBLOCKCHAIN_H