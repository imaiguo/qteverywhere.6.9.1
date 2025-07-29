
#include <QApplication>

#include "Capture.h"

int main(int argc, char** argv){
    QApplication app(argc, argv);
    app.setApplicationName("截图演示");

    Capture cap;
    cap.initUI();
    cap.initConnect();

    app.exec();
    return 0;
}
