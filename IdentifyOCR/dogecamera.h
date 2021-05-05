#ifndef DOGECAMERA_H
#define DOGECAMERA_H

#include <QObject>
#include <QCamera>
#include <QCameraViewfinder>
#include <QCameraImageCapture>

class dogecamera : public QObject
{
    Q_OBJECT
public:
    explicit dogecamera(QObject *parent = nullptr);

private:
    QCamera *m_myCamra;
    QCameraImageCapture *m_myImgCapture;
signals:
    void cameraImgCaptue(int id, const QImage &preview);
private slots:
    void getCameraImg(int id, const QImage &preview);
public slots:
    void startCamera(void);
    void setCameraViewfinder(QVideoWidget *view);
    void startCapture(QString imgName);
};

#endif // DOGECAMERA_H
