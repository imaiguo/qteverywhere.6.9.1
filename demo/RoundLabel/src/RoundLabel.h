#pragma once

#include <QLabel>
#include <QPainter>

class RoundLabel : public QLabel{
    Q_OBJECT
    
public:
    RoundLabel(QWidget *parent = 0);
    ~RoundLabel();
protected:
    void paintEvent(QPaintEvent* e);
};
