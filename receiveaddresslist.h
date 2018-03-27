#ifndef RECEIVEADDRESSLIST_H
#define RECEIVEADDRESSLIST_H

#include <QDialog>

namespace Ui {
class Receiveaddresslist;
}

class Receiveaddresslist : public QDialog
{
    Q_OBJECT
    
public:
    explicit Receiveaddresslist(QWidget *parent = 0);
    ~Receiveaddresslist();

private slots:
    void UpdateTable();
    void onTableClicked();

private:
    Ui::Receiveaddresslist *ui;
};

#endif // RECEIVEADDRESSLIST_H
