
#pragma once

#include <QWidget>

#include "Screen.h"
#include "Menu.h"

//截屏窗口类
class ScreenWidget : public QWidget{
    Q_OBJECT
public:
    explicit ScreenWidget(QWidget *parent = 0);

private:
    QMenu *m_menu  = nullptr;
    Screen *m_screen  = nullptr;
    //保存全屏图像
    QPixmap *m_fullScreen = nullptr;
    //模糊背景图
    QPixmap *m_bgScreen = nullptr;
    //坐标
    QPoint m_movePos;
    // 悬浮菜单
    Menu m_FloatMenu;

    // 屏幕缩放
    float m_Scale = 0.0;

protected:
    void contextMenuEvent(QContextMenuEvent *) override;
    void mousePressEvent(QMouseEvent *) override;
    void mouseMoveEvent(QMouseEvent *) override;
    void mouseReleaseEvent(QMouseEvent *) override;
    void paintEvent(QPaintEvent *) override;
    void showEvent(QShowEvent *) override;
    void hideEvent(QHideEvent *event) override;

public slots:
    void ok();
    void save();
    void saveFullScreen();

signals:
    void hide();
};
