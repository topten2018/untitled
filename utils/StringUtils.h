#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#pragma once

#include <QString>

namespace Utils
{
	QString pars(const QString & src, const QString & open, const QString & close);
	QString guid(int len);
	bool parseCsvLine(const QString str, QStringList & row);
} // namespace Utils

#endif // STRING_UTILS_H
