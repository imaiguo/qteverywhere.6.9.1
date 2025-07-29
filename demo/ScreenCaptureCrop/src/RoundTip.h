
#ifndef RoundTip_H
#define RoundTip_H

#include <QMenu>
#include <QPixmap>
#include <QLabel>
#include <QWidget>
#include <QMouseEvent>

class RoundTip : public QLabel{
	Q_OBJECT
public:
	explicit RoundTip(QWidget *parent = nullptr);
	~RoundTip();

protected:
    void paintEvent(QPaintEvent* e);

signals:

};

#endif // RoundTip_H
