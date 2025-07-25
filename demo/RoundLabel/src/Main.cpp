
#include <QApplication>

#include <QDebug>

#include "RoundLabel.h"
#include "RoundLabelEx.h"

int main(int argc, char **argv){
    QApplication app(argc, argv);
    qDebug() << "Hello World!";
    RoundLabel label;
    // RoundLabelEx label;

    // QString path = "";
    // QImage img;
    // img.load(path);
    // QPixmap pixmap = QPixmap::fromImage(img);

    QPixmap *p1 = new QPixmap(":/image/favicon.png");
    label.setPixmap(*p1);


    QString name  = "Hello World!";
    // label.setString(name);
    label.show();
    app.exec();
}
