
#include "Menu.h"
#include "Config.h"
#include "Singleton.h"
#include "screenwidget.h"

#include "FloatButton.h"
#include "Tools.h"

#include <Windows.h>

#include <QApplication>
#include <QPushButton>

int main(int argc, char *argv[]){
    QApplication app(argc, argv);
    app.setQuitOnLastWindowClosed(false);
    qInstallMessageHandler(Tools::OutputMessage);

    FloatButton btn;
    btn.initUI(":deskcut.jpg");
    btn.show();

    ScreenWidget* capture = PatternTool::Singleton<ScreenWidget>::instance();

    QObject::connect(&btn, &FloatButton::clicked, capture, [capture, &btn](){btn.setHidden(true); Sleep(100); capture->showFullScreen();});
    QObject::connect(capture, &ScreenWidget::hide, &btn, [&btn](){btn.show();});

    // PatternTool::Singleton<ScreenWidget>::instance()->showFullScreen();

    // Menu menu;
    // menu.initUI();
    // menu.show();

    return app.exec();
}
