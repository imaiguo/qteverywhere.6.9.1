
#pragma once

#include <QObject>

class NativeEventFilter;

class ShortcutRegister: public QObject{
    Q_OBJECT
public:
    ShortcutRegister(QObject *parent = nullptr):QObject(parent){};
    ~ShortcutRegister() {};
public:
    void registerShortcut(const NativeEventFilter &filter);

signals:
    void hotkeyCapture();
};

unsigned int nativeModifiers(Qt::KeyboardModifiers modifiers);
unsigned int nativeKeycode(Qt::Key key);

// 参考 http://cppdebug.com/archives/471
