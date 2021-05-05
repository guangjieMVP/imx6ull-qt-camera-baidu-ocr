#ifndef MYCAMERA_H
#define MYCAMERA_H

#include <QObject>

class mycamera : public QObject
{
    Q_OBJECT
public:
    explicit mycamera(QObject *parent = nullptr);

signals:

public slots:
};

#endif // MYCAMERA_H