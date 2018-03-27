#include "worker.h"
#include <QMessageBox>
#include "sockettest.h"

Worker::Worker(QObject *parent) :
    QObject(parent)
{
}


Worker::~Worker() { // Destructor
    // free resources

}
void Worker::BckProcess()
{

}

void Worker::CheckBalance()
{
    SocketTest cTest;
    cTest.GetBalance(jDataAddress.trimmed());
}

