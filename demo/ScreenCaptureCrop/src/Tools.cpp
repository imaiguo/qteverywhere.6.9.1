
#include <QImage>
#include <QMutex>
#include <QDateTime>
#include <QFile>
#include <QTextStream>
#include <QSystemSemaphore>
#include <QSharedMemory>
#include <QDebug>

#include <iostream>

namespace Tools{

QImage AdjustBrightness(QImage Img, int iBrightValue){
    int red, green, blue;
    int pixels = Img.width() * Img.height();
    unsigned int *data = (unsigned int *)Img.bits();
 
    for (int i = 0; i < pixels; ++i)
    {
        red= qRed(data[i])+ iBrightValue;
        red = (red < 0x00) ? 0x00 : (red > 0xff) ? 0xff : red;
        green= qGreen(data[i]) + iBrightValue;
        green = (green < 0x00) ? 0x00 : (green > 0xff) ? 0xff : green;
        blue= qBlue(data[i]) + iBrightValue;
        blue =  (blue  < 0x00) ? 0x00 : (blue  > 0xff) ? 0xff : blue ;
        data[i] = qRgba(red, green, blue, qAlpha(data[i]));
    }
 
    return Img;
}

void OutputMessage(QtMsgType type, const QMessageLogContext &context, const QString &msg){
    static QMutex mutex;
    mutex.lock();
    QString text;
    switch(type){
        case QtDebugMsg:
            text = QString("Debug:");
            break;
        case QtWarningMsg:
            text = QString("Warning:");
            break;
        case QtCriticalMsg:
            text = QString("Critical:");
            break;
        case QtFatalMsg:
            text = QString("Fatal:");
            break;
        case QtInfoMsg:
            text = QString("Info:");
    }
    QString contextInfo = QString("File:[%1:%2]").arg(QString(context.file)).arg(context.line);
    // QString currentDdateTme = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss ddd");
    QString currentDdateTme = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss:zzz");
    QString currentDate = QString("[%1]").arg(currentDdateTme);
    QString message = QString("%1 %2 %3 %4").arg(text).arg(contextInfo).arg(currentDate).arg(msg);
    QFile file("log.txt");
    file.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream textStream(&file);
    textStream << message << "\r\n";
    file.flush();
    file.close();
    mutex.unlock();
    std::cout << message.toStdString() << std::endl;
}

bool RunOnce(){
    QSystemSemaphore sema("LittleFloatButton", 1, QSystemSemaphore::Open);
    sema.acquire();
    static QSharedMemory mem("LittleFloatButtonShareMemory");
    bool result = mem.create(1, QSharedMemory::ReadOnly);
    qDebug() << result;
    sema.release();
    if (result){
        qDebug() << "QSystemSemaphore QSharedMemory Create Succeed.";
        return true;
    }else{
        qDebug() << "QSystemSemaphore QSharedMemory Create failed.";
        return false;
    }

}

}