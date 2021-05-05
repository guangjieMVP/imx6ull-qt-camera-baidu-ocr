#ifndef BAIDU_AI_OCR_H
#define BAIDU_AI_OCR_H

#include <QObject>


class baidu_ai_ocr : public QObject
{
    Q_OBJECT
public:
    explicit baidu_ai_ocr(QObject *parent = nullptr);

signals:

public slots:
};

#endif // BAIDU_AI_OCR_H
