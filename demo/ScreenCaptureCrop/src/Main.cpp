
#include "Menu.h"
#include "Config.h"
#include "Singleton.h"
#include "screenwidget.h"

#include "FloatButton.h"
#include "Tools.h"
#include <Windows.h>

#include <QApplication>
#include <QPushButton>

#include "ShortcutRegister.h"
#include "NativeEventFilter.h"

int main(int argc, char *argv[]){
    QApplication app(argc, argv);
    app.setQuitOnLastWindowClosed(false);
    qInstallMessageHandler(Tools::OutputMessage);

	if(!Tools::RunOnce()){
		return -1;
	}

    // 注册热键
    NativeEventFilter filter(MOD_ALT,'Q');
    app.installNativeEventFilter(&filter);
    ShortcutRegister reg;
    reg.registerShortcut(filter);
    filter.setRegister(&reg);

    // 创建悬浮按钮
    FloatButton btn;
    btn.initUI(":deskcut.jpg");
    btn.show();

    // 创建截图类
    ScreenWidget* capture = PatternTool::Singleton<ScreenWidget>::instance();

    // 信号绑定
    QObject::connect(&btn, &FloatButton::clicked, capture, [capture, &btn](){btn.setHidden(true); Sleep(100); capture->showFullScreen();});
    QObject::connect(capture, &ScreenWidget::hide, &btn, [&btn](){btn.show();});
    QObject::connect(&reg, &ShortcutRegister::hotkeyCapture, capture, [capture, &btn](){btn.setHidden(true); Sleep(100); capture->showFullScreen();});

    // 运行一次截图
    // PatternTool::Singleton<ScreenWidget>::instance()->showFullScreen();

    // Menu menu;
    // menu.initUI();
    // menu.show();

    return app.exec();
}
