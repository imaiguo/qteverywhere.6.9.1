
#include "Capture.h"

#include <QDebug>

#include <windows.h>
#include <atlimage.h>
#include <QMimeData>
#include <QApplication>
#include <QImage>
#include <QClipboard>

void GetDesktopCapture(){
    int width = GetSystemMetrics(SM_CXVIRTUALSCREEN);
    int height = GetSystemMetrics(SM_CYVIRTUALSCREEN);

    // 获取窗口的设备上下文（Device Contexts）
    HDC hdcWindow = GetDC(GetDesktopWindow());  // 要截图的窗口句柄，为空则全屏
    // 获取设备相关信息的尺寸大小
    int nBitPerPixel = GetDeviceCaps(hdcWindow, BITSPIXEL);
    CImage image;
    image.Create(width, height, nBitPerPixel);
    BitBlt(image.GetDC(), // 保存到的目标 图片对象 上下文
           0, 0,     // 起始 x, y 坐标
           width, height,  // 截图宽高
           hdcWindow,      // 截取对象的 上下文句柄
           0,0,
           /*m_pParentView->x(), m_pParentView->y(),*/           // 指定源矩形区域左上角的 X, y 逻辑坐标
           SRCCOPY
           );
    // 释放 DC句柄
    ReleaseDC(nullptr, hdcWindow);
    // 释放图片上下文
    image.ReleaseDC();
    WCHAR wfile[256];
    memset(wfile,0, sizeof(wfile));
    CString cPath = L"tmp.png";
    HRESULT result = image.Save(cPath, Gdiplus::ImageFormatPNG);
    QImage shot = QImage("tmp.png");

    QMimeData * mimeData = new QMimeData;
    mimeData->setImageData(shot);
    qApp->clipboard()->setMimeData(mimeData);
}

Capture::Capture(QObject *parent): QObject(parent){

}

Capture::~Capture(){
    
}

bool Capture::initUI(){
    m_btn.resize(250, 200);
    m_btn.setText("截图");
    m_btn.show();
    return true;
}

void Capture::initConnect(){
    connect(&m_btn, &QPushButton::clicked, this, &Capture::onCaptureBtn);
}

void Capture::onCaptureBtn(){
    qDebug() << "onCaptureBtn." ;
    m_btn.hide();
    GetDesktopCapture();
}
