#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "dogecamera.h"
#include <QMediaPlayer>

#include <baiduaithread.h>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

signals:
    void sendPlatePic(QString picPath);
public slots:
     void doCapture(void);
     void handleImageCapture(int id, const QImage &preview);
     void displayPlateNumber(QString number);
private:
    Ui::Widget *ui;
    dogecamera *camera;
    QMediaPlayer *player;
    baiduaithread *baidthread;
    QThread *thread;
};

#endif // WIDGET_H
