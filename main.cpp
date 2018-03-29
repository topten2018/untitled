#include "mainwindow.h"
#include <QDebug>
#include <QtDebug>
#include <QFile>
#include <QTextStream>
#include <QtGlobal>
#include <QDir>
#include <QtGlobal>
#include <QApplication>

#include <QSystemSemaphore>
#include <QSharedMemory>
#include <QMessageBox>


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
	QStringList paths = QCoreApplication::libraryPaths();
	paths.append(".");
	paths.append("imageformats");
	paths.append("audio");
	paths.append("platforms");
	paths.append("sqldrivers");
	paths.append("mediaservice");
	QCoreApplication::setLibraryPaths(paths);

#ifdef DEBUG_TEST
#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
    qInstallMessageHandler(crashMessageOutput);
#else
    qInstallMsgHandler(crashMessageOutput);
#endif
#endif
    QApplication a(argc, argv);

	QSystemSemaphore semaphore(QCoreApplication::arguments()[0], 1);  
	semaphore.acquire();

#ifndef Q_OS_WIN32
						
	QSharedMemory nix_fix_shared_memory(QCoreApplication::arguments()[0] + "shared_mem_name");
	if (nix_fix_shared_memory.attach()) {
		nix_fix_shared_memory.detach();
	}
#endif

	QSharedMemory sharedMemory(QCoreApplication::arguments()[0] + "shared_mem_name"); 
	bool is_running;            
	if (sharedMemory.attach())  
	{							
		is_running = true;      
	}
	else
	{
		sharedMemory.create(1); 
		is_running = false;     
	}
	semaphore.release();        

								
								
	if (is_running)
	{
		QMessageBox msgBox;
		msgBox.setIcon(QMessageBox::Warning);
		msgBox.setText(QObject::tr("Application already running."));
		msgBox.exec();
		return 1;
	}

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
