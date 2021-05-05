#-------------------------------------------------
#
# Project created by QtCreator 2021-04-16T22:33:43
#
#-------------------------------------------------

QT       += core gui
QT += multimedia
QT += multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = IdentifyOCR
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        widget.cpp \
    json/json_reader.cpp \
    json/json_value.cpp \
    json/json_valueiterator.inl \
    json/json_writer.cpp \
    dogecamera.cpp \
    baiduaithread.cpp


HEADERS += \
        widget.h \
    json/allocator.h \
    json/assertions.h \
    json/config.h \
    json/forwards.h \
    json/json.h \
    json/json_features.h \
    json/json_tool.h \
    json/reader.h \
    json/value.h \
    json/version.h \
    json/writer.h \
    aip-cpp-sdk-4.15.4/base/base.h \
    aip-cpp-sdk-4.15.4/base/base64.h \
    aip-cpp-sdk-4.15.4/base/http.h \
    aip-cpp-sdk-4.15.4/base/utils.h \
    aip-cpp-sdk-4.15.4/ocr.h \
    dogecamera.h \
    aip-cpp-sdk-4.15.4/speech.h \
    baiduaithread.h

FORMS += \
        widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

unix:!macx: LIBS += -L$$PWD/../../../../../usr/local/openssl/lib/ -lssl

INCLUDEPATH += $$PWD/../../../../../usr/local/openssl/include
DEPENDPATH += $$PWD/../../../../../usr/local/openssl/include

unix:!macx: LIBS += -L$$PWD/../../../../../usr/local/openssl/lib/ -lcrypto

INCLUDEPATH += $$PWD/../../../../../usr/local/openssl/include
DEPENDPATH += $$PWD/../../../../../usr/local/openssl/include

unix:!macx: LIBS += -L$$PWD/../../../../../usr/local/curl/lib/ -lcurl

INCLUDEPATH += $$PWD/../../../../../usr/local/curl/include
DEPENDPATH += $$PWD/../../../../../usr/local/curl/include
