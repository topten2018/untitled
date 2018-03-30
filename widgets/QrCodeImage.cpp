#include "QrCodeImage.h"

#include "utils/QrEncoder.h"

QrCodeImage::QrCodeImage()
	: QImage(1, 1, QImage::Format_Mono)
{

}
QrCodeImage::QrCodeImage(int w, int h)
	: QImage(w, h, QImage::Format_Mono)
{

}
QrCodeImage::~QrCodeImage()
{

}
void QrCodeImage::setText(const QString & str)
{
	int  levelIndex = 1;
	int  versionIndex = 0;
	bool bExtent = true;
	int  maskIndex = -1;

	QrEncoder qrEncode;


	bool successfulEncoding = qrEncode.encodeData(levelIndex, versionIndex, bExtent, maskIndex, str.toUtf8().data());
	if (!successfulEncoding)
	{
		fill(1);
		return;
	}

	int qrImageSize = qrEncode.symbleSize();

	int encodeImageSize = qrImageSize + (QR_MARGIN * 2);

	QrCodeImage encodeImage(encodeImageSize, encodeImageSize);
	encodeImage.fill(1);

	// Создать двумерный образ кода
	for (int i = 0; i < qrImageSize; i++)
		for (int j = 0; j < qrImageSize; j++)
			if (qrEncode.at(i, j))
				encodeImage.setPixel(i + QR_MARGIN, j + QR_MARGIN, 0);

	*this = std::move(encodeImage);
}