
#include "RoundLabel.h"

#include <QPainterPath>
// class QPainterPath;

RoundLabel::RoundLabel(QWidget* parent) : QLabel(parent){
    setWindowFlags(Qt::FramelessWindowHint | Qt::Window | Qt::WindowStaysOnTopHint | Qt::Tool);
    resize(100, 100);
}

RoundLabel::~RoundLabel(){
   
}

void RoundLabel::paintEvent(QPaintEvent* e){
    if(pixmap().isNull()){
        QLabel::paintEvent(e);
    }else{
       QPainter painter(this);
       painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
       QPainterPath path;
       int round = qMin(width(),height());
       path.addEllipse(0,0,round,round);
       painter.setClipPath(path);
       painter.drawPixmap(-1,-1,width() + 2, height() + 2, pixmap());
    } 
}