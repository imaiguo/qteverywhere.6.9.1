
class QImage;

namespace Tools{

QImage AdjustBrightness(QImage Img, int iBrightValue);
void OutputMessage(QtMsgType type, const QMessageLogContext &context, const QString &msg);
bool RunOnce();
}