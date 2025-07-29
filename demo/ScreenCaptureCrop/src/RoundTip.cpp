
#include <windows.h>
#include <windowsx.h>

#include <QIcon>
#include <QDebug>
#include <QPainter>
#include <QPainterPath>
#include <QApplication>
#include <QMessageBox>

#include "RoundTip.h"

#include "Config.h"
#include "Tools.h"

RoundTip::RoundTip(QWidget *parent) : QLabel(parent){
	setMouseTracking(true);
	setWindowFlags(Qt::FramelessWindowHint | Qt::Window | Qt::WindowStaysOnTopHint | Qt::Tool);
	setAttribute(Qt::WA_TranslucentBackground, true);
	resize(Config::WindowSize, Config::ButtonSize);
}

RoundTip::~RoundTip(){

}

void RoundTip::paintEvent(QPaintEvent* e){
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing); 
    painter.setBrush(QBrush(Qt::black));
    painter.setPen(Qt::transparent);
    QRect winRect = rect();
    winRect.setWidth(winRect.width() - 1);
    winRect.setHeight(winRect.height() - 1);
    painter.drawRoundedRect(winRect, 20, 20);

    //绘制文字
    QString name = text();
    int y = name.length();
    QFont font;
    font.setPixelSize(14);
    font.setFamily("黑体");
    font.setBold(true);
    painter.setPen(QPen(Qt::white, 5, Qt::SolidLine));//设置画笔形式
    painter.setFont(font);

    painter.drawText(8, height()/2 + 4, name);
}
