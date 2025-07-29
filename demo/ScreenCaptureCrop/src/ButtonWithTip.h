
#ifndef ButtonWithTip_H
#define ButtonWithTip_H

#include <QMenu>
#include <QPixmap>
#include <QLabel>
#include <QWidget>
#include <QMouseEvent>

#include "RoundTip.h"

class ButtonWithTip : public QLabel{
	Q_OBJECT
public:
	explicit ButtonWithTip(QWidget *parent = nullptr);
	~ButtonWithTip();
	bool initUI(QString icon = ":/image/icon.png");
	void SetName(QString name);

public:
	void mousePressEvent(QMouseEvent* e) override;
	void mouseReleaseEvent(QMouseEvent *ev) override;
    void enterEvent(QEnterEvent *event) override;
    void leaveEvent(QEvent *event) override;
	void initConnection();
	void reSizeTipWidth(int w);

private:
	QPixmap m_iconLeave;
	QPixmap m_iconEnter;
	QPixmap m_iconPress;
    QString m_Name;
    RoundTip m_Tip;

protected:
    void paintEvent(QPaintEvent* e);
signals:

};

#endif // ButtonWithTip_H
