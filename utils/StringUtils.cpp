#include "StringUtils.h"

#include <QUuid> 
#include <QTextStream>
#include <QStringList>

namespace Utils
{
QString pars(const QString & src, const QString & open, const QString & close)
{
	QString res;
	int s = src.indexOf(open);
	if (close.isEmpty() && s >= 0)
	{
		return src.mid(s + open.length(), -1);
	}
	int e = src.indexOf(close, s + open.length());
	if (s >= 0 && e > 0)
	{
		return src.mid(s + open.length(), e - s - open.length());
	}

	return "";
}
QString guid(int len)
{
	QString res = QUuid::createUuid().toString();
	res = res.replace("-", "");
	res = res.replace("{", "");
	res = res.replace("}", "");
	return res.left(len);
}
bool parseCsvLine(const QString str, QStringList & row)
{
	static const int delta[][5] = {
		//  ,    "   \n    ?  eof
		{ 1,   2,  -1,   0,  -1 }, // 0: parsing (store char)
		{ 1,   2,  -1,   0,  -1 }, // 1: parsing (store column)
		{ 3,   4,   3,   3,  -2 }, // 2: quote entered (no-op)
		{ 3,   4,   3,   3,  -2 }, // 3: parsing inside quotes (store char)
		{ 1,   3,  -1,   0,  -1 }, // 4: quote exited (no-op)
								   // -1: end of row, store column, success
								   // -2: eof inside quotes
	};

	row.clear();

	if (str.isEmpty())
		return false;

	int state = 0, t;
	QChar ch;
	QString cell;
	int ind = 0;
	while (ind <= str.size()) 
	{
		if (ind == str.size())
		{
			t = 4;
			ind++;
		}
		else {
			ch = str[ind++];
			if (ch == ',') t = 0;
			else if (ch == '\"') t = 1;
			else if (ch == '\n') t = 2;
			else t = 3;
		}

		state = delta[state][t];

		switch (state) {
		case 0:
		case 3:
			cell += ch;
			break;
		case -1:
		case 1:
			row.append(cell);
			cell = "";
			break;
		}
	}

	if (state == -2)
		return false;

	return true;
}
} // namespace Utils
