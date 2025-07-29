
#include "Menu.h"
#include "Config.h"

Menu::Menu(QWidget *parent):QWidget(parent){
    setWindowFlags(Qt::FramelessWindowHint | Qt::Window | Qt::WindowStaysOnTopHint | Qt::Tool);
    resize(180, Config::ButtonSize);
}

bool Menu::initUI(){
    setAttribute(Qt::WA_TranslucentBackground, false);
    // 确认截图
    int pos = 10;
    m_btnOK.setParent(this);
    m_btnOK.initUI(":ok.png");
    m_btnOK.SetName("确认");
    m_btnOK.move(pos, 10);
    m_btnOK.reSizeTipWidth(46);

    // 取消
    pos = pos + Config::ButtonSize + 5;
    m_btnClose.setParent(this);
    m_btnClose.initUI(":close.png");
    m_btnClose.SetName("取消");
    m_btnClose.move(pos, 10);
    m_btnClose.reSizeTipWidth(46);


    // 保存截图到文件
    pos = pos + Config::ButtonSize + 5;
    m_btnCropSave.setParent(this);
    m_btnCropSave.initUI(":crop.png");
    m_btnCropSave.SetName("保存");
    m_btnCropSave.move(pos, 10);
    m_btnCropSave.reSizeTipWidth(46);


    // 保存全屏到文件
    pos = pos + Config::ButtonSize + 5;
    m_btnFullSave.setParent(this);
    m_btnFullSave.initUI(":fullscreen.png");
    m_btnFullSave.SetName("保存全屏");
    m_btnFullSave.move(pos, 10);
    m_btnFullSave.reSizeTipWidth(78);

    return true;
}