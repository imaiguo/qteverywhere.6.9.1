
#pragma once

#include <QWidget>

#include "Screen.h"

//截屏窗口类
class ScreenWidget : public QWidget{
    Q_OBJECT
public:
    explicit ScreenWidget(QWidget *parent = 0);

private:
    QMenu *m_menu;
    Screen *m_screen;
    //保存全屏图像
    QPixmap *m_fullScreen;
    //模糊背景图
    QPixmap *m_bgScreen;      
    //坐标
    QPoint m_movePos;

protected:
    void contextMenuEvent(QContextMenuEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void paintEvent(QPaintEvent *);
    void showEvent(QShowEvent *);

private slots:
    void saveScreenCrop();
    void saveScreenCropToPath();
    void saveFullScreen();
    void saveFullToPath();
};
