#include "baidu_ai_ocr.h"
#include "aip-cpp-sdk-4.15.4/ocr.h"
#include "aip-cpp-sdk-4.15.4/speech.h"

static std::string app_id = "23984344";
static std::string api_key = "fvfDW7uoGglfIR1ypBvDMKKZ";
static std::string secret_key = "i5ZElDfPWTZ3Z7GVtmM5bvWFp5FGuT3u";

static aip::Ocr client(app_id, api_key, secret_key);

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

baidu_ai_ocr::baidu_ai_ocr(QObject *parent) : QObject(parent)
{

}
