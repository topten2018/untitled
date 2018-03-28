#ifndef GUI_UTILS_H
#define GUI_UTILS_H

#include <QApplication>
#include <QTimer>

namespace Utils
{
	class WaitGuard
	{
	public:
		WaitGuard()
		{
			QApplication::setOverrideCursor(Qt::WaitCursor);
			QApplication::processEvents();
		}
		~WaitGuard()
		{
			QApplication::restoreOverrideCursor();
			QApplication::processEvents();
		}
	};

	class WaitGuard10Sec : public QObject
	{
		Q_OBJECT
		bool m_bRestored;
	public:
		WaitGuard10Sec() : m_bRestored(false)
		{
			QApplication::setOverrideCursor(Qt::WaitCursor);
			QApplication::processEvents();
			QTimer::singleShot(5000, this, SLOT(restore()));
		}
		~WaitGuard10Sec()
		{
			if (!m_bRestored)
			{
				QApplication::restoreOverrideCursor();
				QApplication::processEvents();
			}
		}
	public slots:
		void restore()
		{
			if (!m_bRestored)
			{
				QApplication::restoreOverrideCursor();
				QApplication::processEvents();
			}
			m_bRestored = true;
		}
	};
} // namespace Utils

#endif // GUI_UTILS_H
