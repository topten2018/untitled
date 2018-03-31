#include "sockettest.h"
#include "QString";
#include "QSettings";
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QRegExp>

extern QString s_exeLocation;

SocketTest::SocketTest(QObject *parent) :
    QObject(parent)
{
}

bool UpdateFinished = false;
bool MoneySent = false;
bool jUpdate1 = false;
QString jUpdatedBalance="";

QString jDataAddress="";
QString jSendToAddress="";
QString jGlobalSumToSend="";
QString jStatisticsHistory = "";

QString jAddressInfo="";
QString jAddressInClipboard="";
QString jAddressInUri="";
QString jSendingAddressesOUTList = "";











void SocketTest::Ser(QString j)
{
    QSettings sett("my");

    sett.setValue("value1", j);
}

void SocketTest::GetVar()
{
    QSettings settings("parameter");
    QString myvar1 = settings.value("value1").toString();


}

void SocketTest::SendMoney()
{
    socket = new QTcpSocket(this);
    socket->connectToHost("18.222.33.249", 10116);

    if(socket->waitForConnected(15000))
    {
        qDebug() << "Connected!";

        // send
        QString j = "send:"  + jDataAddress + ":" + jSendToAddress + ":" + jGlobalSumToSend;
        const char *c = j.toLatin1();
        socket->write(c);
        socket->waitForBytesWritten(1000);
        socket->waitForReadyRead(3000);
        QString temp="";
        while (socket->bytesAvailable())
            {
                 temp= socket->readAll();
            }

     //   QString k = socket->readAll();
    //    QSettings sett("my");
    //    sett.setValue("balance", temp);

MoneySent = true;
        QMessageBox msgBox;
        msgBox.setText("Transaction has been performed");
        msgBox.exec();


      /*  msgBox.setText("!!!!");
        msgBox.exec();
        msgBox.setText(temp+ "!!!!");
        msgBox.exec();
        */


/*
        QRegExp rx( "(\\d+)\\[");
        int pos = rx.indexIn( temp );
        QStringList list = rx.capturedTexts();
        //msgBox.setText(list[1]);
        //msgBox.exec();

        QSettings sett("my");
        sett.setValue("balance", list[1]);
        jUpdatedBalance = list[1];
        UpdateFinished=true;
        */

/*
        QString jFileContent = "";
        QString filename = "Data5.txt";
            QFile file(filename);
            if (file.open(QIODevice::ReadWrite))
            {

                QTextStream stream(&file);
                stream << temp<< endl;


            }
            */























        socket->close();

    }
    else
    {
        qDebug() << "Not connected!";
    }

    // sent

    // got

    // closed

}

void SocketTest::GetBalance(QString Addr)
{
    socket = new QTcpSocket(this);
    //socket->connectToHost("bogotobogo.com", 80);
    socket->connectToHost("18.222.33.249", 10116);

    if(socket->waitForConnected(15000))
    {
        qDebug() << "Connected!";

        // send
        QString j = "balance:"+Addr;


/*
        char* cstr;

        cstr = new char [j.size()+1];
        strcpy( cstr, j.c_str() );
        */

        const char *c = j.toLatin1();

        socket->write(c);
        socket->waitForBytesWritten(1000);
        socket->waitForReadyRead(3000);
        qDebug() << "Reading: " << socket->bytesAvailable();

       // qDebug() << socket->readAll();
       // QString k = socket->readAll();
       // QSettings sett("my");
       // sett.setValue("value1", k);
        //Ser(k);
        QString temp="";
        while (socket->bytesAvailable())
            {
                 temp= socket->readAll();
            }

     //   QString k = socket->readAll();
    //    QSettings sett("my");
    //    sett.setValue("balance", temp);


//        QMessageBox msgBox;
      /*  msgBox.setText("!!!!");
        msgBox.exec();
        msgBox.setText(temp+ "!!!!");
        msgBox.exec();
        */



        QRegExp rx( "(\\d+)\\[");
        int pos = rx.indexIn( temp );
        QStringList list = rx.capturedTexts();
        //msgBox.setText(list[1]);
        //msgBox.exec();



   if (temp.contains("["))
       {
        QRegExp rxt( "\\[(.*)\\]");
        int posd = rxt.indexIn( temp );
        QStringList listoftemp = rxt.capturedTexts();
        jStatisticsHistory = listoftemp[1];


       }



/*
        QRegExp rxt2( "(.*);");
        int posd2 = rxt2.indexIn( jStatisticsHistory );
        QStringList listoftemp2 = rxt2.capturedTexts();

       QString sd = listoftemp2[2];
       */





     /*   QMessageBox msgBox;
        msgBox.setText(sd);
        msgBox.exec();
        */







/*
        QSettings sett("my");
        sett.setValue("balance", list[1]);
        */
        jUpdatedBalance = list[1];
        UpdateFinished=true;



        QString jFileContent = "";
        QString filename = s_exeLocation + "Data6.txt";
            QFile file(filename);
            if (file.open(QIODevice::ReadWrite))
            {

                QTextStream stream(&file);
                stream << jStatisticsHistory<< endl;


            }
























        socket->close();

    }
    else
    {
        qDebug() << "Not connected!";
    }

    // sent

    // got

    // closed

}


void SocketTest::Connect()
{
    socket = new QTcpSocket(this);
    //socket->connectToHost("bogotobogo.com", 80);
    socket->connectToHost("18.222.33.249", 10116);

    if(socket->waitForConnected(15000))
    {
        qDebug() << "Connected!";

      /*
        QRegExp rx("(\\:)");
        QStringList query = jDataAddress.split(rx);
        */



        QString j = "getaddr:"+jDataAddress;

         const char *c = j.toLatin1();


        // send
        socket->write(c);
        socket->waitForBytesWritten(1000);
        socket->waitForReadyRead(3000);
        qDebug() << "Reading: " << socket->bytesAvailable();

       // qDebug() << socket->readAll();
       // QString k = socket->readAll();
       // QSettings sett("my");
       // sett.setValue("value1", k);
        //Ser(k);
        QString temp="";
        while (socket->bytesAvailable())
            {
                 temp = socket->readAll();
            }

     //   QString k = socket->readAll();
        QSettings sett("my");
        sett.setValue("value1", temp);








        socket->close();

    }
    else
    {
        qDebug() << "Not connected!";
    }

    // sent

    // got

    // closed
}
