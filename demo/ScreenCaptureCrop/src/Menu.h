
#pragma once

#include "ButtonWithTip.h"

#include <QWidget>

class Menu: public QWidget{
    Q_OBJECT
public:
    explicit Menu(QWidget *parent = nullptr);
    bool initUI();

private:
    ButtonWithTip m_btnOK;
    ButtonWithTip m_btnClose;
    ButtonWithTip m_btnCropSave;
    ButtonWithTip m_btnFullSave;
};
