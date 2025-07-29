
#include "Singleton.h"
#include "screenwidget.h"
#include "Menu.h"

#include <QApplication>

int main(int argc, char *argv[]){
    QApplication app(argc, argv);
    // app.setFont(QFont("Microsoft Yahei", 9));


    PatternTool::Singleton<ScreenWidget>::instance()->showFullScreen();

    // Menu menu;
    // menu.initUI();
    // menu.show();

    return app.exec();
}
