

#include <QObject>

class Worker : public QObject
{
    Q_OBJECT
public:
    explicit Worker(QObject *parent = 0);

       ~Worker();
    
signals:
    
public slots:
    void BckProcess();
    void CheckBalance();
    
};


