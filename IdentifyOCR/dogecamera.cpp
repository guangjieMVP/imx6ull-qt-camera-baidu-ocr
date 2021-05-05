#include "dogecamera.h"

dogecamera::dogecamera(QObject *parent) : QObject(parent)
{
    m_myCamra = new QCamera(this);
    m_myImgCapture = new QCameraImageCapture(m_myCamra);
    m_myCamra->setCaptureMode(QCamera::CaptureStillImage);
    connect(m_myImgCapture, &QCameraImageCapture::imageCaptured, this, &dogecamera::getCameraImg);
}

void dogecamera::getCameraImg(int id, const QImage &preview)
{
    emit cameraImgCaptue(id, preview);
}

void dogecamera::startCamera()
{
    m_myCamra->start();
}

void dogecamera::setCameraViewfinder(QVideoWidget *view)
{
    m_myCamra->setViewfinder(view);
}

void dogecamera::startCapture(QString imgName)
{
    m_myImgCapture->capture(imgName);
}
