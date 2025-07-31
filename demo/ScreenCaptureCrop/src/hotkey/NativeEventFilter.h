
#pragma once

#include "Windows.h"

#include <QAbstractNativeEventFilter>

class ShortcutRegister;

class NativeEventFilter :public QAbstractNativeEventFilter {
public:
    NativeEventFilter(const unsigned int& mod, const unsigned int& key, ShortcutRegister * reg=nullptr);
public:
    bool nativeEventFilter(const QByteArray &eventType, void *message, qintptr *result) override;
    unsigned int mod, key;
    ShortcutRegister * m_register = nullptr;
};
