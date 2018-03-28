#ifndef AUTOSAVER_H
#define AUTOSAVER_H

#include <QtCore/QObject>
#include <QtCore/QTimer>
#include <QtCore/QTime>

/*
    This class will call the save() slot on the parent object when the parent changes.
    It will wait several seconds after changed() to combining multiple changes and
    prevent continuous writing to disk.
  */
class AutoSaver : public QObject 
{

Q_OBJECT

public:
    AutoSaver(QObject *parent);
    ~AutoSaver();
    void saveIfNeccessary();

public slots:
    void changeOccurred();

private slots:
	void onTimer();


private:
    QTimer	m_Timer;
    QTime	m_FirstChange;

	volatile bool m_bModified;
};

#endif // AUTOSAVER_H

