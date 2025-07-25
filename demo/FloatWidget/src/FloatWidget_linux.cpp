#include "flwidget_linux.h"
#include <QLayout>
#include <QMouseEvent>

namespace
{
	#define ResizeHandleWidth 10
}

FLWidget_Linux::FLWidget_Linux(QWidget *parent) : QWidget(parent)
{
	setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
	setStyleSheet("background-color:red;");

	QHBoxLayout* layoutMain = new QHBoxLayout(this);
	layoutMain->setContentsMargins(ResizeHandleWidth, ResizeHandleWidth, ResizeHandleWidth, ResizeHandleWidth);
	this->setLayout(layoutMain);
	resizingCornerEdge = XUtils::CornerEdge::kInvalid;
	setMouseTracking(true);

	XUtils::SetMouseTransparent(this, true);

	setAttribute(Qt::WA_ShowModal);

	resize(400, 400);
}


void FLWidget_Linux::mouseMoveEvent(QMouseEvent *event)
{
	const int x = event->x();
	const int y = event->y();

	if (resizingCornerEdge == XUtils::CornerEdge::kInvalid)
	{
		XUtils::UpdateCursorShape(this, x, y, this->layout()->contentsMargins(), ResizeHandleWidth);
	}

	return QWidget::mouseMoveEvent(event);
}

void FLWidget_Linux::mousePressEvent(QMouseEvent *event)
{

	const int x = event->x();
	const int y = event->y();
	if (event->button() == Qt::LeftButton)
	{
		const XUtils::CornerEdge ce = XUtils::GetCornerEdge(this, x, y, this->layout()->contentsMargins(), ResizeHandleWidth);
		if (ce != XUtils::CornerEdge::kInvalid)
		{
			resizingCornerEdge = ce;
			//send x11 move event dont send mouserrelease event
			XUtils::SendButtonRelease(this, event->pos(), event->globalPos());
			XUtils::StartResizing(this, QCursor::pos(), ce);
		}
	}

	return QWidget::mousePressEvent(event);
}

void FLWidget_Linux::resizeEvent(QResizeEvent *e)
{

	int resizeHandleWidth = ResizeHandleWidth;
	XUtils::SetWindowExtents(this, this->layout()->contentsMargins(), resizeHandleWidth);

	return QWidget::resizeEvent(e);
}

void FLWidget_Linux::mouseReleaseEvent(QMouseEvent *event)
{
	resizingCornerEdge = XUtils::CornerEdge::kInvalid;

	return QWidget::mouseReleaseEvent(event);
}

