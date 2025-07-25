#ifndef FLOATWIDGET_H
#define FLOATWIDGET_H

#include <QWidget>
#include <QMouseEvent>

class FloatWidget : public QWidget
{
	Q_OBJECT
public:
	explicit FloatWidget(QWidget *parent = nullptr);
	~FloatWidget();

public:
	bool nativeEvent(const QByteArray &eventType, void *message, qintptr *result) override;
	// bool nativeEvent(const QByteArray &eventType, void *message, qintptr *result);
	void mousePressEvent(QMouseEvent* e) override;
	void mouseMoveEvent(QMouseEvent* e) override;

private:
	int m_bouderWidth;
	QPoint m_curPos;

signals:

};

#endif // FLOATWIDGET_H
