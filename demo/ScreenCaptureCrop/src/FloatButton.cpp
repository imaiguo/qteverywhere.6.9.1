
#include <windows.h>
#include <windowsx.h>

#include <QPainter>
#include <QPainterPath>
#include <QDebug>
#include <QApplication>
#include <QIcon>
#include <QDir>

#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
#include <QScreen>
#else
#include <QDesktopWidget>
#endif

#include "FloatButton.h"
#include "Config.h"
#include "Tools.h"
#include "Singleton.h"
#include "ScreenWidget.h"

FloatButton::FloatButton(QWidget *parent) : QLabel(parent){
	setMouseTracking(true);
    //配置主界面属性: 置顶 无边框 任务栏不显示
	setWindowFlags(Qt::FramelessWindowHint | Qt::Window | Qt::WindowStaysOnTopHint | Qt::Tool);
	setAttribute(Qt::WA_TranslucentBackground, true);
	resize(Config::WindowSize, Config::WindowSize);
}

FloatButton::~FloatButton(){

}

bool FloatButton::initUI(QString icon){

    setWindowIcon(QIcon(icon));
	m_iconLeave = QPixmap(icon);
	setPixmap(m_iconLeave);

	QImage image1 = QImage(icon);
	QImage imageEnter = Tools::AdjustBrightness(image1, Config::ButtonBright);
	m_iconEnter = QPixmap::fromImage(imageEnter);

	QImage image2 = QImage(icon);
	QImage imagePress = Tools::AdjustBrightness(image2, -Config::ButtonBright);
	m_iconPress = QPixmap::fromImage(imagePress);

    // 计算并设置小蓝人靠近屏幕边缘距离
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
    QRect screenRect = QApplication::primaryScreen()->geometry();
#else
    QRect screenRect = QApplication::desktop()->screenGeometry();
#endif

    m_TrayMenu.addAction(QIcon(":deskcut.jpg"), QObject::tr("开始截图"), [&]() {
        qDebug()<<"打开开始截图.";
        this->setHidden(true);
        Sleep(100);
        PatternTool::Singleton<ScreenWidget>::instance()->showFullScreen();
    });

    m_TrayMenu.addAction(QIcon(":info.png"), QObject::tr("关于"), []() { qDebug()<<"Application About."; qApp->aboutQt(); });
    m_TrayMenu.addAction(QIcon(":exit.jpg"), QObject::tr("退出"), []() { qDebug()<<"Application Exit."; qApp->exit(); });

    m_SystemTray.setObjectName("FloatButton");
    m_SystemTray.setIcon(QIcon(icon));
    m_SystemTray.setToolTip("开始截图");
    m_SystemTray.setContextMenu(&m_TrayMenu);
    m_SystemTray.show();

    m_Tip.setText("截图 Alt+Q");
    m_Tip.resize(94, Config::ButtonSize);

    int x = screenRect.width() - Config::PaddingSide - Config::WindowSize;
    int y = screenRect.height() - Config::PaddingBottom - Config::WindowSize;
    move(x, y);

    QDir dir;
    dir.mkdir(QString("%1/save/").arg(qApp->applicationDirPath()));

    initConnection();
	return true;
}

void FloatButton::onTrayActive(QSystemTrayIcon::ActivationReason reason){
    if( reason == QSystemTrayIcon::ActivationReason::Trigger){
        qDebug()<<"onTrayActive...[" << reason << "]";
        this->setHidden(true);
        Sleep(100);
        PatternTool::Singleton<ScreenWidget>::instance()->showFullScreen();
    }
}

void FloatButton::initConnection(){
    connect(&m_SystemTray, &QSystemTrayIcon::activated, this, &FloatButton::onTrayActive);
}

void FloatButton::mousePressEvent(QMouseEvent *e){
	if (e->button() == Qt::LeftButton){
        m_MousePos = pos();
        m_curPos = e->pos();
        setPixmap(m_iconPress);
        m_Tip.hide();
    }

	QWidget::mousePressEvent(e);
}

void FloatButton::mouseMoveEvent(QMouseEvent *e){
	if (e->buttons() & Qt::LeftButton){
        m_MousePos = pos();
		move(e->pos() + pos() - m_curPos);
    }

	QWidget::mouseMoveEvent(e);
}

void FloatButton::mouseReleaseEvent(QMouseEvent *ev){
    if(ev->button() & Qt::LeftButton){
        if(m_MousePos == pos()){
            emit clicked();
        }
    }else if(ev->button() & Qt::RightButton){
        int x = pos().x() - 130;
        int y = pos().y();
        //配置菜单 在屏幕犄角旮旯 能够完全显示
        if(y < 20)
            y =20;

#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
    int sHigth = QApplication::primaryScreen()->geometry().height();
#else
    int sHigth = QApplication::desktop()->screenGeometry().height();
#endif

        if (y > sHigth - 180)
            y = sHigth - 180;

        if(x < 140)
            x = 140;

        m_TrayMenu.move(x, y);
        m_TrayMenu.show();
    }

    setPixmap(m_iconEnter);

    QLabel::mouseReleaseEvent(ev);
}

void FloatButton::enterEvent(QEnterEvent *ev){
    setCursor(QCursor(Qt::PointingHandCursor));
	setPixmap(m_iconEnter);
    QPoint curPos = pos();
    // tip靠右显示
    if(curPos.x() <= Config::PaddingSide + Config::MenuWidth)
        m_Tip.move(curPos.x() + Config::WindowSize, curPos.y() + Config::WindowSize/2 - m_Tip.height()/2);
    // tip靠左显示
    else
        m_Tip.move(curPos.x() - m_Tip.width(), curPos.y() + Config::WindowSize/2 - m_Tip.height()/2);
    m_Tip.show();

    QLabel::enterEvent(ev);
}

// 判断鼠标坐标在 菜单按钮区域 则 不隐藏菜单
void FloatButton::leaveEvent(QEvent *ev){
    qDebug() << "FloatButton leaveEvent";
	setPixmap(m_iconLeave);
    m_Tip.hide();
}

void FloatButton::paintEvent(QPaintEvent* e){
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
