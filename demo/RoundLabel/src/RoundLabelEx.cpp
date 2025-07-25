
#include "RoundLabelEx.h"

#include <QPainterPath>

RoundLabelEx::RoundLabelEx(QWidget *parent):QLabel(parent) {
}

RoundLabelEx::~RoundLabelEx(){
}

void RoundLabelEx::setString(QString& str){
    strName = str;
}

void RoundLabelEx::paintEvent(QPaintEvent* e){
    if(pixmap().isNull()){
        QLabel::paintEvent(e);
    }else{
        if(strName.length()<=0) return;

        QPainter painter(this);
        QPainterPath path;

        painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
        int round = qMin(width(),height());
        round = round - 30;
        path.addEllipse(15, 15, round, round);
        painter.setClipPath(path);
        painter.drawPixmap(15, 15, width()-30, height()-30, pixmap());

        //绘制矩形
        // painter.setPen(QPen(Qt::white,6,Qt::Nopen));  //设置画笔形式
        painter.setBrush(QBrush(QColor(0, 0, 0, 150), Qt::SolidPattern));
        painter.drawRect(0, height()-50, width(), 50);

        //绘制文字
        int x,y = strName.length();
        QFont font;
        font.setPixelSize(14);
        font.setFamily("黑体");
        painter.setPen(QPen(Qt::white,5,Qt::SolidLine));//设置画笔形式
        painter.setFont(font);

        x = (width()-30)/2 - 7*y/2;
        painter.drawText(x,height()-15-17,strName);
    }
}
