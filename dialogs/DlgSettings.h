#pragma once

#include <QDialog>
#include "ui_DlgSettings.h"

class DlgSettings : public QDialog
{
	Q_OBJECT

public:
	DlgSettings(QWidget *parent = Q_NULLPTR);
	~DlgSettings();

private:
	Ui::DlgSettings ui;
};
