#include "Singleton.h"
#include "screenwidget.h"

#include <QApplication>

int main(int argc, char *argv[]){
    QApplication app(argc, argv);
    app.setFont(QFont("Microsoft Yahei", 9));


    PatternTool::Singleton<ScreenWidget>::instance()->showFullScreen();

    return app.exec();
}
