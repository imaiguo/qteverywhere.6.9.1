#include "floatwidget_win.h"

#include <windows.h>
#include <windowsx.h>

#include <QMouseEvent>


namespace
{
	constexpr int BOUDERWIDTH = 10;
}

FloatWidget::FloatWidget(QWidget *parent) : QWidget(parent), m_bouderWidth(BOUDERWIDTH)
{
	setMouseTracking(true);
	setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
	// setWindowFlags(Qt::CustomizeWindowHint);

	setStyleSheet("background:red");
	setAttribute(Qt::WA_ShowModal);
	resize(500, 500);
}

FloatWidget::~FloatWidget()
{

}

void FloatWidget::mousePressEvent(QMouseEvent *e)
{

	if (e->button() == Qt::LeftButton)
		m_curPos = e->pos();
	return QWidget::mousePressEvent(e);
}
void FloatWidget::mouseMoveEvent(QMouseEvent *e)
{
	if (e->buttons() & Qt::LeftButton)
		move(e->pos() + pos() - m_curPos);

	return QWidget::mouseMoveEvent(e);
}

bool FloatWidget::nativeEvent(const QByteArray &eventType, void *message, qintptr *result)
{
	MSG* msg = (MSG*)message;
	switch(msg->message)
	{
		case WM_NCHITTEST:
			int xPos = GET_X_LPARAM(msg->lParam) - this->frameGeometry().x();
			int yPos = GET_Y_LPARAM(msg->lParam) - this->frameGeometry().y();
			int nUseFulWidth = width() - m_bouderWidth;
			int nUseFulHeight = height() - m_bouderWidth;
			if (xPos < m_bouderWidth && yPos < m_bouderWidth)	
				*result = HTTOPLEFT;
			else if (xPos>= nUseFulWidth && yPos < m_bouderWidth)
				*result = HTTOPRIGHT;
			else if (xPos < m_bouderWidth && yPos >= nUseFulHeight)	
				*result = HTBOTTOMLEFT;
			else if (xPos >= nUseFulWidth && yPos >= nUseFulHeight)	
				*result = HTBOTTOMRIGHT;
			else if (xPos < m_bouderWidth)	//左边
				*result =  HTLEFT;
			else if (xPos >= nUseFulWidth)	//右边
				*result = HTRIGHT;
			else if (yPos < m_bouderWidth)	//上边
				*result = HTTOP;
			else if (yPos >= nUseFulHeight)	//下边
				*result = HTBOTTOM;
			else
				return false;

			return true;
		}

	return QWidget::nativeEvent(eventType, message, result);	//此处返回false，留给其他事件处理器处理

}


