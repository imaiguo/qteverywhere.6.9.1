
#include <windows.h>
#include <windowsx.h>

#include <QPainter>
#include <QPainterPath>
#include <QDebug>
#include <QApplication>
#include <QIcon>
#include <QMessageBox>

#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
#include <QScreen>
#else
#include <QDesktopWidget>
#endif

#include "ButtonWithTip.h"

#include "Config.h"
#include "Tools.h"

ButtonWithTip::ButtonWithTip(QWidget *parent) : QLabel(parent){
	setMouseTracking(true);
	setWindowFlags(Qt::FramelessWindowHint | Qt::Window | Qt::WindowStaysOnTopHint | Qt::Tool);
	setAttribute(Qt::WA_TranslucentBackground, true);
	resize(Config::ButtonSize/2, Config::ButtonSize/2);
}

ButtonWithTip::~ButtonWithTip(){

}

void ButtonWithTip::SetName(QString name){
    m_Name = name;
    m_Tip.setText(m_Name);
}

void ButtonWithTip::reSizeTipWidth(int w){
    m_Tip.resize(w, Config::ButtonSize);
}

bool ButtonWithTip::initUI(QString icon){
	m_iconLeave = QPixmap(icon);
	setPixmap(m_iconLeave);

	QImage image1 = QImage(icon);
	QImage imageEnter = Tools::AdjustBrightness(image1, Config::ButtonBright * 2 );
	m_iconEnter = QPixmap::fromImage(imageEnter);

	QImage image2 = QImage(icon);
	QImage imagePress = Tools::AdjustBrightness(image2, -Config::ButtonBright * 2);
	m_iconPress = QPixmap::fromImage(imagePress);

    m_Name = "友好提示";
	return true;
}

void ButtonWithTip::initConnection(){
    // connect(&m_SystemTray, &QSystemTrayIcon::activated, this, &ButtonWithTip::onTrayActive);
}


void ButtonWithTip::mousePressEvent(QMouseEvent *e){
	if (e->button() == Qt::LeftButton)
        setPixmap(m_iconPress);

	return QWidget::mousePressEvent(e);
}


void ButtonWithTip::mouseReleaseEvent(QMouseEvent *ev){
    QMessageBox::information(this, m_Name, "功能正努力实现中...");

    setPixmap(m_iconEnter);
    QLabel::mouseReleaseEvent(ev);
}

void ButtonWithTip::enterEvent(QEnterEvent *ev){
    qInfo()<<"ButtonWithTip::enterEvent";
	setPixmap(m_iconEnter);
    setCursor(QCursor(Qt::PointingHandCursor));
    QPoint globalPos = ((QWidget*)parent())->mapToGlobal(pos());
    // Tip靠上显示
    m_Tip.move(globalPos.x() + 5, globalPos.y() + height()*1.5);

    m_Tip.show();
}

void ButtonWithTip::leaveEvent(QEvent *ev){
    qInfo()<<"ButtonWithTip::leaveEvent";
	setPixmap(m_iconLeave);
    m_Tip.hide();
}

void ButtonWithTip::paintEvent(QPaintEvent* e){
    if(pixmap().isNull()){
        QLabel::paintEvent(e);
    }else{
        QPainter painter(this);
        painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
        QPainterPath path;
        int round = qMax(width(),height());
        path.addRect(0, 0, round, round);
        painter.setClipPath(path);
        painter.drawPixmap(0, 0, width(), height(), pixmap());
    }
}
