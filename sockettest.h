#ifndef SOCKETTEST_H
#define SOCKETTEST_H

#include <QObject>
#include <QTcpSocket>
#include <QDebug>
extern bool UpdateFinished;
extern bool MoneySent;
extern bool jUpdate1;
extern QString jUpdatedBalance;
extern QString jDataAddress;
extern QString jSendToAddress;
extern QString jGlobalSumToSend;
extern QString jStatisticsHistory;
extern QString jAddressInfo;
extern QString jAddressInClipboard;
extern QString jAddressInUri;
extern QString jSendingAddressesOUTList ;

class SocketTest : public QObject
{
    Q_OBJECT
public:
    explicit SocketTest(QObject *parent = 0);

    void Connect();
    void Ser( QString k);
    void GetVar();
    void GetBalance(QString A);
    void SendMoney();


signals:

public slots:


private:
    QTcpSocket *socket;

};

#endif // SOCKETTEST_H
