#ifndef DLGBIP38TOOL_H
#define DLGBIP38TOOL_H

#include <QWidget>
#include "ui_DlgBip38Tool.h"

class DlgBip38Tool : public QDialog
{
	Q_OBJECT

public:
	DlgBip38Tool(QWidget *parent = Q_NULLPTR);
	~DlgBip38Tool();

private:
	Ui::DlgBip38Tool ui;
};
#endif // DLGBIP38TOOL_H