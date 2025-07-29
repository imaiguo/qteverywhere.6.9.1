#pragma once

#include <QWidget>
#include <QMenu>
#include <QPoint>
#include <QSize>

//截屏对象类
class Screen{
public:
    enum STATUS {SELECT, MOV};
    Screen() {}
    Screen(QSize size);

    void setStart(QPoint pos);
    void setEnd(QPoint pos);
    QPoint getStart();
    QPoint getEnd();

    QPoint getLeftUp();
    QPoint getRightDown();

    STATUS getStatus();
    void setStatus(STATUS m_status);

    int width();
    int height();
    // 检测pos是否在截图区域内
    bool isInArea(QPoint pos);
    // 按 p 移动截图区域
    void move(QPoint p);

private:
    //记录 截图区域 左上角、右下角
    QPoint m_leftUpPos, m_rightDownPos;
    //记录 鼠标开始位置、结束位置
    QPoint m_startPos, m_endPos;
    //记录屏幕大小
    int m_maxWidth, m_maxHeight;
    //三个状态: 选择区域、移动区域、设置width height
    STATUS m_status;

private:
    //比较两位置，判断左上角、右下角
    void cmpPoint(QPoint &s, QPoint &e);
};
