#include "baiduaithread.h"


#include "./aip-cpp-sdk-4.15.4/ocr.h"
#include "aip-cpp-sdk-4.15.4/speech.h"

   // 设置APPID/AK/SK
std::string app_id = "23984344";
std::string api_key = "fvfDW7uoGglfIR1ypBvDMKKZ";
static std::string secret_key = "i5ZElDfPWTZ3Z7GVtmM5bvWFp5FGuT3u";

static aip::Ocr client(app_id, api_key, secret_key);

// 设置APPID/AK/SK
static std::string Speechapp_id = "24057838";
static std::string Speechapi_key = "ecayDkA6BmTVvv6hnwbkYzji";
static std::string Speechsecret_key = "16qm9MIOqdnGO9nvV9UWibc28zC4xUBx";

static aip::Speech speechClient(Speechapp_id, Speechapi_key, Speechsecret_key);
//get
static std::string _GetPlateNumber(std::string PicPath)
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

static int _speechtts(std::string fileName, std::string plateNumber)
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
//    if (ofile.is_open())
//    {
//        ofile.close();
//    }
}


baiduaithread::baiduaithread(QObject *parent) : QObject(parent)
{

}

void baiduaithread::getPlateNumber(QString picPath)
{
    std::string plateNumber =  _GetPlateNumber(picPath.toStdString());
    emit sendPlateNumber(QString::fromStdString(plateNumber));
    printf("get plate number\r\n");
    if (_speechtts("plate.mp3", plateNumber) == 0)
    {
        system("mplayer plate.mp3 &");
    }
    printf("get plate number\r\n");
}

void baiduaithread::getPlateNumberThreadFun()
{
//    while (1)
//    {
//        printf("curent id : \r\n");
        QThread::msleep(100);
//    }
      printf("bai du ai thread start\r\n");
}
