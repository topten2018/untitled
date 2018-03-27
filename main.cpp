#include "mainwindow.h"
#include <QDebug>
#include <QtDebug>
#include <QFile>
#include <QTextStream>
#include <QtGlobal>

#include <QtGlobal>
#include <QtWidgets/QApplication>


#define DEBUG_TEST


/*
void myMessageHandler(QtMsgType type, const QMessageLogContext &, const QString & msg)
{
    QString txt;
    switch (type) {
    case QtDebugMsg:
        txt = QString("Debug: %1").arg(msg);
        break;
    case QtWarningMsg:
        txt = QString("Warning: %1").arg(msg);
    break;
    case QtCriticalMsg:
        txt = QString("Critical: %1").arg(msg);
    break;
    case QtFatalMsg:
        txt = QString("Fatal: %1").arg(msg);
    break;
    }
    QFile outFile("log");
    outFile.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream ts(&outFile);
    ts << txt << endl;
}
*/

#ifdef DEBUG_TEST
#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
void crashMessageOutput(QtMsgType type, const QMessageLogContext &, const QString & str)
{
    const char * msg = str.toStdString().c_str();
#else
void crashMessageOutput(QtMsgType type, const char *msg)
{
#endif
    QString txt;
    switch (type) {
    case QtDebugMsg:
        txt = QString("Debug: %1").arg(msg);
        break;
    case QtWarningMsg:
        txt = QString("Warning: %1").arg(msg);
    break;
    case QtCriticalMsg:
        txt = QString("Critical: %1").arg(msg);
    break;
    case QtFatalMsg:
        txt = QString("Fatal: %1").arg(msg);
    break;
    }
    QFile outFile("log");
    outFile.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream ts(&outFile);
    ts << txt << endl;
}
#endif
int main(int argc, char *argv[])
{
#ifdef DEBUG_TEST
#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
    qInstallMessageHandler(crashMessageOutput);
#else
    qInstallMsgHandler(crashMessageOutput);
#endif
#endif
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    
    return a.exec();
}
