#ifndef QRCODEIMAGE_H
#define QRCODEIMAGE_H

#include <QImage>

class QrCodeImage : public QImage
{
public:
	QrCodeImage();
	QrCodeImage(int w, int h);
	virtual ~QrCodeImage();

public slots:
	void setText(const QString & str);

};

#endif // QRCODEIMAGE_H
