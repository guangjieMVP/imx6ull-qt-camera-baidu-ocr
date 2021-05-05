#include "widget.h"
#include "ui_widget.h"
#include <QTimer>
#include <QProcess>


#define USE_BAIDU_AI   0

#if USE_BAIDU_AI

#include "./aip-cpp-sdk-4.15.4/ocr.h"
#include "aip-cpp-sdk-4.15.4/speech.h"


   // 设置APPID/AK/SK
std::string app_id = "23984344";
std::string api_key = "fvfDW7uoGglfIR1ypBvDMKKZ";
std::string secret_key = "i5ZElDfPWTZ3Z7GVtmM5bvWFp5FGuT3u";

aip::Ocr client(app_id, api_key, secret_key);

// 设置APPID/AK/SK
std::string Speechapp_id = "24057838";
std::string Speechapi_key = "ecayDkA6BmTVvv6hnwbkYzji";
std::string Speechsecret_key = "16qm9MIOqdnGO9nvV9UWibc28zC4xUBx";

aip::Speech speechClient(Speechapp_id, Speechapi_key, Speechsecret_key);
//get
static std::string GetPlateNumber(std::string PicPath)
{
    Json::Value result;

    std::string image;
    aip::get_file_content(PicPath.c_str(), &image);

    // 调用车牌识别
    result = client.license_plate(image, aip::null);

    // 如果有可选参数
    std::map<std::string, std::string> options;
    options["multi_detect"] = "true";

    // 带参数调用车牌识别
    result = client.license_plate(image, options);
    if (result["error_code"].isNull())    //
    {
        return (result["words_result"][0]["number"].asString() + ",欢迎光临!");
    }
    else
    {
        return ("识别失败");
    }
    return ("识别失败");
}


static int speechtts(std::string fileName, std::string plateNumber)
{
    std::ofstream ofile;
    std::string file_ret;
    std::map<std::string, std::string> options;
    options["spd"] = "5";
    options["vol"] = "10";
    options["per"] = "0";
    options["pit"] = "6";

    // 合成成功的二进制数据写入文件中
    ofile.open(fileName, std::ios::out | std::ios::binary);

    // 不带可选参数调用
    //Json::Value result = client.text2audio("百度语音合成测试", aip::null, file_ret);

    // 带可选参数调用, 参数参考参数列表中的可选参数
    Json::Value result = speechClient.text2audio(plateNumber, options, file_ret);

    // 如果file_ret为不为空则说明合成成功，返回mp3文件内容回结果
    if (!file_ret.empty())
    {
        ofile << file_ret;
        return 0;
    }
    else
    {
        // 服务端合成错误
        std::cout << result.toStyledString();
        return -1;
    }
    if (ofile.is_open())
    {
        ofile.close();
    }
}
#endif

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    camera = new dogecamera(this);
    camera->setCameraViewfinder(ui->cameraFrame);

    player = new QMediaPlayer(this);

    ui->picturLabel->setStyleSheet("QLabel{border:2px solid rgb(0, 255, 0);}");

    connect(ui->identifyButton, SIGNAL(clicked()), this, SLOT(doCapture()));
    connect(camera, &dogecamera::cameraImgCaptue, this, &Widget::handleImageCapture);

    baiduaithread *baidthread = new baiduaithread();
    QThread *thread = new QThread();

    connect(this, SIGNAL(sendPlatePic(QString)), baidthread, SLOT(getPlateNumber(QString)));
    connect(baidthread, SIGNAL(sendPlateNumber(QString)), this, SLOT(displayPlateNumber(QString)));
    connect(thread, SIGNAL(started()), baidthread, SLOT(getPlateNumberThreadFun()));
    baidthread->moveToThread(thread);
    thread->start();

    camera->startCamera();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::doCapture()
{
    camera->startCapture("plate.jpg");
    ui->identifyButton->setText("拍照识别");
    return;
}

void Widget::handleImageCapture(int id, const QImage &preview)
{
    QPixmap img = QPixmap::fromImage(preview);

    QString plate = QString("plate.jpg");
    img.save(plate);

    ui->picturLabel->setScaledContents(true);
    int with = ui->picturLabel->width();
    int height = ui->picturLabel->height();

    //按label比例缩放
    QPixmap fitpixmap = img.scaled(with, height, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    ui->picturLabel->setPixmap(fitpixmap);       //

    emit sendPlatePic(plate);      //send picture path
    printf("send picture path\r\n");

#if USE_BAIDU_AI
    std::string result = GetPlateNumber("plate.jpg");
    ui->retultLineEdit->setText(QString::fromStdString(result));

    //remove("plate.mp3");

    if (speechtts("plate.mp3", result) == 0)
    {
//        player->setMedia(QUrl::fromLocalFile("plate.mp3"));
//        player->setVolume(100);
//        player->play();
//        QProcess *myProcess = new QProcess();
//        QString process("gplay-1.0 plate.mp3");
//        myProcess->start(process);  //启动程序
        system("mplayer plate.mp3 &");
    }
    else
    {
        qDebug() << "make speech failed";
    }
#endif
}

void Widget::displayPlateNumber(QString number)
{
    ui->retultLineEdit->setText(number);
}

