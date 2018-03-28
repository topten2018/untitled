#include "mainwindow.h"
#include <QDebug>
#include <QtDebug>
#include <QFile>
#include <QTextStream>
#include <QtGlobal>
#include <QDir>
#include <QtGlobal>
#include <QApplication>


#define DEBUG_TEST

QString s_LogFileName;
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
void crashMessageOutput(QtMsgType type, const QMessageLogContext &, const QString & msg)
{
#else
void crashMessageOutput(QtMsgType type, const char *str)
{
	QString msg = str;
#endif
	if (s_LogFileName.isEmpty())
		return;
    QString txt;
    switch (type) 
	{
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
    QFile outFile(s_LogFileName);
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

	s_LogFileName = QCoreApplication::arguments()[0];
	int i = s_LogFileName.lastIndexOf(QDir::separator());
	if (i == -1)
		s_LogFileName = "";
	else
		s_LogFileName = s_LogFileName.left(i + 1);

	s_LogFileName += "log";

    MainWindow w;
    w.show();
    
    return a.exec();
}
