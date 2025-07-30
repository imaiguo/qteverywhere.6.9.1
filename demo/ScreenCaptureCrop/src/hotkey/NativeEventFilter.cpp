
#include "NativeEventFilter.h"
#include "ShortcutRegister.h"

#include <QDebug>

NativeEventFilter::NativeEventFilter(const unsigned int& mod, const unsigned int& key){
    this->mod = mod;
    this->key = key;
}

bool NativeEventFilter::nativeEventFilter(const QByteArray &eventType, void *message, qintptr *result){
    MSG* msg = static_cast<MSG*>(message);
    if (msg->message == WM_HOTKEY){
        const quint32 keycode = HIWORD(msg->lParam);
        const quint32 modifiers = LOWORD(msg->lParam);

        if (keycode == key && mod == modifiers)
            qDebug() << "shortcut trigger!";
            emit m_register->hotkeyCapture();
    }

    return false;
}

void NativeEventFilter::setRegister(ShortcutRegister * reg){
    m_register = reg;
}
