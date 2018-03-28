#include "Autosaver.h"

#include <QtCore/QDir>
#include <QtCore/QCoreApplication>
#include <QApplication>
#include <QtCore/QMetaObject>
#include <QDebug>

#define AUTOSAVE_IN  1000 * 3  // seconds
#define MAXWAIT      1000 * 15 // seconds

AutoSaver::AutoSaver(QObject *parent) 
	: QObject(parent)
	, m_bModified(false)
{
    Q_ASSERT(parent);

	connect(&m_Timer, &QTimer::timeout, this, &AutoSaver::onTimer);
}

AutoSaver::~AutoSaver()
{
    if (m_Timer.isActive())
        qDebug() << "AutoSaver: still active when destroyed, changes not saved.";

	saveIfNeccessary();
}

void AutoSaver::changeOccurred()
{
	m_bModified = true;

    if (m_FirstChange.isNull())
        m_FirstChange.start();

    if (m_FirstChange.elapsed() > MAXWAIT) 
	{
        saveIfNeccessary();
    }
	else 
	{
		m_Timer.singleShot(AUTOSAVE_IN, this, SLOT(onTimer()));	
    }
}

void AutoSaver::onTimer()
{
	saveIfNeccessary();
}

void AutoSaver::saveIfNeccessary()
{
    if (!m_bModified)
        return;

	m_bModified = false;

    m_Timer.stop();
    m_FirstChange = QTime();
    if (!QMetaObject::invokeMethod(parent(), "save", Qt::DirectConnection)) 
	{
        qDebug() << "AutoSaver: error invoking slot save() on parent";
    }
}

