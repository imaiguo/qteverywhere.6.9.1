
#include <QMutex>
#include <QApplication>
#include <QPainter>
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
#include <QScreen>
#else
#include <QDesktopWidget>
#endif
#include <QFileDialog>
#include <QEvent>
#include <QDateTime>
#include <QStringList>

#include "Screen.h"
#include <QScreen>

Screen::Screen(QSize size){
    m_maxWidth = size.width();
    m_maxHeight = size.height();

    m_startPos = QPoint(-1, -1);
    m_endPos = m_startPos;
    m_leftUpPos = m_startPos;
    m_rightDownPos = m_startPos;
    m_status = SELECT;
}

int Screen::width(){
    return m_maxWidth;
}

int Screen::height(){
    return m_maxHeight;
}

Screen::STATUS Screen::getStatus(){
    return m_status;
}

void Screen::setStatus(STATUS m_status){
    this->m_status = m_status;
}

void Screen::setEnd(QPoint pos){
    m_endPos = pos;
    m_leftUpPos = m_startPos;
    m_rightDownPos = m_endPos;
    cmpPoint(m_leftUpPos, m_rightDownPos);
}

void Screen::setStart(QPoint pos){
    m_startPos = pos;
}

QPoint Screen::getEnd(){
    return m_endPos;
}

QPoint Screen::getStart(){
    return m_startPos;
}

QPoint Screen::getLeftUp(){
    return m_leftUpPos;
}

QPoint Screen::getRightDown(){
    return m_rightDownPos;
}

bool Screen::isInArea(QPoint pos){
    if (pos.x() > m_leftUpPos.x() && pos.x() < m_rightDownPos.x() && pos.y() > m_leftUpPos.y() && pos.y() < m_rightDownPos.y()) {
        return true;
    }

    return false;
}

void Screen::move(QPoint p){
    int lx = m_leftUpPos.x() + p.x();
    int ly = m_leftUpPos.y() + p.y();
    int rx = m_rightDownPos.x() + p.x();
    int ry = m_rightDownPos.y() + p.y();

    if (lx < 0) {
        lx = 0;
        rx -= p.x();
    }

    if (ly < 0) {
        ly = 0;
        ry -= p.y();
    }

    if (rx > m_maxWidth)  {
        rx = m_maxWidth;
        lx -= p.x();
    }

    if (ry > m_maxHeight) {
        ry = m_maxHeight;
        ly -= p.y();
    }

    m_leftUpPos = QPoint(lx, ly);
    m_rightDownPos = QPoint(rx, ry);
    m_startPos = m_leftUpPos;
    m_endPos = m_rightDownPos;
}

void Screen::cmpPoint(QPoint &leftTop, QPoint &rightDown){
    QPoint l = leftTop;
    QPoint r = rightDown;

    if (l.x() <= r.x()) {
        if (l.y() <= r.y()) {
            ;
        } else {
            leftTop.setY(r.y());
            rightDown.setY(l.y());
        }
    } else {
        if (l.y() < r.y()) {
            leftTop.setX(r.x());
            rightDown.setX(l.x());
        } else {
            QPoint tmp;
            tmp = leftTop;
            leftTop = rightDown;
            rightDown = tmp;
        }
    }
}
