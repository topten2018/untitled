#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#pragma once

#include <QString>

namespace Utils
{
	void rotateFiles(const QString & file, int depth);
	void createDir(const QString & dir, const QString & subDir);
} // namespace Utils

#endif // FILE_UTILS_H
