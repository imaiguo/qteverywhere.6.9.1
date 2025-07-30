
#ifndef FloatButton_H
#define FloatButton_H

#include <QMenu>
#include <QPixmap>
#include <QLabel>
#include <QWidget>
#include <QMouseEvent>
#include <QSystemTrayIcon>
#include <QPropertyAnimation>

#include "RoundTip.h"

class FloatButton : public QLabel{
	Q_OBJECT
public:
	explicit FloatButton(QWidget *parent = nullptr);
	~FloatButton();
	bool initUI(QString icon = ":/image/icon.png");

public:
	void mousePressEvent(QMouseEvent* e) override;
	void mouseMoveEvent(QMouseEvent* e) override;
	void mouseReleaseEvent(QMouseEvent *ev) override;
    void enterEvent(QEnterEvent*event) override;
    void leaveEvent(QEvent *event) override;

	void initConnection();
	void onTrayActive(QSystemTrayIcon::ActivationReason reason);

private:

	QPoint m_curPos;
	QPoint m_MousePos;
	QPixmap m_iconLeave;
	QPixmap m_iconEnter;
	QPixmap m_iconPress;

	QSystemTrayIcon m_SystemTray;
	QMenu m_TrayMenu;

	RoundTip m_Tip;

protected:
    void paintEvent(QPaintEvent* e) override;

signals:
	void clicked();
};

#endif // FloatButton_H
