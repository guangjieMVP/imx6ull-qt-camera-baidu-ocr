#ifndef BAIDUAITHREAD_H
#define BAIDUAITHREAD_H

#include <QObject>
#include <QThread>

class baiduaithread : public QObject
{
    Q_OBJECT
public:
    explicit baiduaithread(QObject *parent = nullptr);

signals :
    void sendPlateNumber(QString number);
public slots:
    void getPlateNumber(QString picPath);
    void getPlateNumberThreadFun(void);
};

#endif // BAIDUAITHREAD_H
