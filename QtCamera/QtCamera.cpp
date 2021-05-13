#include "QtCamera.h"
#include <QDebug>
#include <QLabel>
#include <QZxing.h>

QtCamera::QtCamera(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	ui.label->setFixedSize(QSize(640, 480));

	foreach(QByteArray var, QCamera::availableDevices())
	{
		ui.cB_Devices->addItem(QCamera::deviceDescription(var));
	}
}

void QtCamera::startCamera()
{
	camera = new QCamera(QCamera::availableDevices().at(ui.cB_Devices->currentIndex()), this);
	frameGrabber = new CameraFrameGrabber();
	camera->setViewfinder(frameGrabber);
	connect(frameGrabber, &CameraFrameGrabber::frameAvailable, this, &QtCamera::ShowFrame);
	camera->start();
}

unsigned char img[1024*1024*16];

void QtCamera::ShowFrame(const QImage frame)
{
	ui.label->clear();
	memcpy(img, frame.bits(), frame.byteCount());
	QImage image2(img,
		frame.width(),
		frame.height(),
		frame.format());
	image2 = image2.mirrored(false, true);
	ui.label->setPixmap(QPixmap::fromImage(image2));
	QZXing decoder(static_cast<QZXing::DecoderFormat>(QZXing::DecoderFormat_QR_CODE | QZXing::DecoderFormat_CODE_128), this);
	QString ret = decoder.decodeImage(image2);
	if (ret.isEmpty() == false)
		qDebug() << ret;
}

void QtCamera::stopCamera()
{
	camera->stop();
}