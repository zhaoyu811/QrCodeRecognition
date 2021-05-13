#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtCamera.h"
#include <QtMultimedia>
#include <QtMultimediaWidgets>
#include <QCamera>
//#include <opencv.hpp>
#include "cameraframegrabber.h"

class QtCamera : public QMainWindow
{
    Q_OBJECT

public:
    QtCamera(QWidget *parent = Q_NULLPTR);

public Q_SLOTS:

	void startCamera();
	void stopCamera();
	void ShowFrame(const QImage frame);

private:
    Ui::QtCameraClass ui;
	QCamera *camera;
	CameraFrameGrabber *frameGrabber;
	QPixmap pixmap;
};
