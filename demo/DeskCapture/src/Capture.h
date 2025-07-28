#pragma once

#include <QPushButton>

class Capture : public QObject{
	Q_OBJECT
public:
    explicit Capture(QObject *parent = nullptr);
    ~Capture();

public:
    bool initUI();
    void initConnect();

public slots:
    void onCaptureBtn();

private:
    QPushButton m_btn;
};
