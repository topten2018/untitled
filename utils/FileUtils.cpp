#include "FileUtils.h"

#include <QDir>
#include <QFileInfo>

namespace Utils
{

void rotateFiles(const QString & file, int depth)
{
	QFileInfo fi(file);

	QDir dir = fi.dir();
	QString filename = fi.fileName();
	QString ext;

	int pos = filename.lastIndexOf(".");
	if (pos > 0)
	{
		ext = filename.right(filename.length() - pos - 1);
		filename = filename.left(pos);
	}

	dir.remove(QObject::tr("%1.%2.%3").arg(filename).arg(depth).arg(ext));

	for (int i = depth; i > 0; i--)
	{
		if (i == 1)
		{
			dir.rename(QObject::tr("%1.%2").arg(filename).arg(ext), QObject::tr("%1.%2.%3").arg(filename).arg(i).arg(ext));
		}
		else
		{
			dir.rename(QObject::tr("%1.%2.%3").arg(filename).arg(i - 1).arg(ext)
				, QObject::tr("%1.%2.%3").arg(filename).arg(i).arg(ext));
		}
	}
}
void createDir(const QString & d, const QString & subDir)
{
	QDir dir(d);
	if (QDir(subDir).exists())
		return;
	dir.mkdir(subDir);
}

} // namespace Utils
