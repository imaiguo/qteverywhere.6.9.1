#pragma once

#include <QLabel>
#include <QPainter>

class RoundLabelEx : public QLabel{
    Q_OBJECT
public:
    RoundLabelEx(QWidget *parent = 0);
    ~RoundLabelEx();
    void setString(QString& str);
    
protected:
    void paintEvent(QPaintEvent* e);

private:
    QString strName;
};

