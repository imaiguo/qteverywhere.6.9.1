
#include <QPainter>
#include <QShortcut>
#include <QFileDialog>
#include <QMutex>
#include <QMutexLocker>
#include <QApplication>
#include <QDateTime>
#include <QMouseEvent>
#include <QMimeData>
#include <QApplication>
#include <QClipboard>
#include <QMessageBox>
#include <QStandardPaths>
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
#include <QScreen>
#else
#include <QDesktopWidget>
#endif

#include <Windows.h>

#include "ScreenWidget.h"
#include "Config.h"

#define STRDATETIME qPrintable(QDateTime::currentDateTime().toString("yyyy-MM-dd-HHmmss"))

ScreenWidget::ScreenWidget(QWidget *parent) : QWidget(parent){
    // 调试时注释如下一行代码
    setWindowFlags(Qt::FramelessWindowHint | Qt::Window | Qt::WindowStaysOnTopHint | Qt::Tool);

    m_menu = new QMenu(this);
    m_menu->addAction(QIcon(":ok.png"), "确认", this, &ScreenWidget::ok);
    m_menu->addAction(QIcon(":crop.png"), "保存", this, &ScreenWidget::save);
    m_menu->addAction(QIcon(":fullscreen.png"), "保存全屏", this, &ScreenWidget::saveFullScreen);
    m_menu->addAction(QIcon(":close.png"), "取消", this, [this](){this->setHidden(true);});
    //取得屏幕大小
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
    QRect screenRect = QApplication::primaryScreen()->geometry();
#else
    QRect screenRect = QApplication::desktop()->screenGeometry();
#endif
    m_screen = new Screen(screenRect.size());
    //保存全屏图像
    m_fullScreen = new QPixmap();

    m_FloatMenu.setParent(this);
    m_FloatMenu.initUI();
    m_FloatMenu.move(screenRect.width() - 180 - 50, screenRect.height() - Config::ButtonSize*2);

    QShortcut *m_EscCut = new QShortcut(tr("Esc"), this);
    m_EscCut->setAutoRepeat(false);

    QShortcut *m_Return = new QShortcut(Qt::Key_Return, this);
    QShortcut *m_Enter = new QShortcut(Qt::Key_Enter, this);
    m_Enter->setAutoRepeat(false);
    m_Return->setAutoRepeat(false);

    connect(m_EscCut, &QShortcut::activated, this, [this](){this->setHidden(true);});
    connect(m_Return, &QShortcut::activated, this, [this](){qDebug()<< "QKeySequence(Qt::Key_Return) actived."; this->ok();});
    connect(m_Enter, &QShortcut::activated, this, [this](){qDebug()<< "QKeySequence(Qt::Key_Enter) actived."; this->ok();});
}

void ScreenWidget::paintEvent(QPaintEvent *){
    int x = m_screen->getLeftUp().x();
    int y = m_screen->getLeftUp().y();
    int w = m_screen->getRightDown().x() - x;
    int h = m_screen->getRightDown().y() - y;

    QPainter painter(this);

    QPen pen;
    pen.setColor(Qt::green);
    pen.setWidth(2);
    pen.setStyle(Qt::DotLine);
    painter.setPen(pen);
    painter.drawPixmap(0, 0, *m_bgScreen);

    if (w != 0 && h != 0) {
        painter.drawPixmap(x, y, m_fullScreen->copy(x, y, w, h));
    }

    painter.drawRect(x, y, w, h);

    pen.setColor(Qt::blue);
    painter.setPen(pen);
    painter.drawText(x + 2, y - 8, tr("截图范围：( %1 x %2 ) - ( %3 x %4 )  图片大小：( %5 x %6 )").arg(x).arg(y).arg(x + w).arg(y + h).arg(w).arg(h));

    if(w > 0)
        m_FloatMenu.move(m_screen->getRightDown().x() - 180, m_screen->getRightDown().y());
}

void ScreenWidget::showEvent(QShowEvent *ev){
    // 每次重新显示截图蒙版 重置m_screen区域
    QPoint point(-1, -1);
    m_screen->setStart(point);
    m_screen->setEnd(point);

    QScreen *pscreen = QApplication::primaryScreen();
    // *m_fullScreen = pscreen->grabWindow(0, 0, 0, m_screen->width(), m_screen->height());
    *m_fullScreen = pscreen->grabWindow((WId)GetDesktopWindow(), 0, 0, m_screen->width(), m_screen->height());

    //设置透明度实现模糊背景
    QPixmap pix(m_screen->width(), m_screen->height());
    pix.fill((QColor(160, 160, 160, 200)));
    m_bgScreen = new QPixmap(*m_fullScreen);
    QPainter p(m_bgScreen);
    p.drawPixmap(0, 0, pix);

    //取得屏幕大小
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
    QRect screenRect = QApplication::primaryScreen()->geometry();
#else
    QRect screenRect = QApplication::desktop()->screenGeometry();
#endif
    m_FloatMenu.move(screenRect.width() - 180 - 50, screenRect.height() - Config::ButtonSize*2);
    QWidget::showEvent(ev);
}

void ScreenWidget::ok(){
    int x = m_screen->getLeftUp().x();
    int y = m_screen->getLeftUp().y();
    int w = m_screen->getRightDown().x() - x;
    int h = m_screen->getRightDown().y() - y;

    if(w < 10 || h < 10 ){
        qDebug() << "所选区域无效";
        return;
    }

    QString fileName = QString("%1/save/screen_%2.png").arg(qApp->applicationDirPath()).arg(STRDATETIME);
    QPixmap tmp = m_fullScreen->copy(x, y, w, h);
    tmp.save(fileName, "png");

    // 存储到剪切板
    QMimeData * mimeData = new QMimeData;
    mimeData->setImageData(tmp.toImage());
    qApp->clipboard()->setMimeData(mimeData);
    setHidden(true);
}

void ScreenWidget::saveFullScreen(){
    // QString name = QString("%1.png").arg(STRDATETIME);
    QString desktopPath = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
    desktopPath.append(QString("/%1.png").arg(STRDATETIME));
    QString fileName = QFileDialog::getSaveFileName(this, "保存图片", desktopPath, "png Files (*.png)");
    if (fileName.length() > 0) {
        if (!fileName.endsWith(".png"))
            fileName += ".png";
        m_fullScreen->save(fileName, "png");
        setHidden(true);
    }
}

void ScreenWidget::save(){
    int x = m_screen->getLeftUp().x();
    int y = m_screen->getLeftUp().y();
    int w = m_screen->getRightDown().x() - x;
    int h = m_screen->getRightDown().y() - y;
    if(w < 10 || h < 10 ){
        qDebug() << "所选区域无效";
        return;
    }

    // QString name = QString("%1.png").arg(STRDATETIME);
    QString desktopPath = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
    desktopPath.append(QString("/%1.png").arg(STRDATETIME));
    QString fileName = QFileDialog::getSaveFileName(this, "保存图片", desktopPath, "png Files (*.png)");
    if (fileName.length() > 0) {
        if (!fileName.endsWith(".png"))
            fileName += ".png";
        m_fullScreen->copy(x, y, w, h).save(fileName, "png");
        setHidden(true);
    }
}

void ScreenWidget::mouseMoveEvent(QMouseEvent *ev){
    if (m_screen->getStatus() == Screen::SELECT) {
        m_screen->setEnd(ev->pos());
    } else if (m_screen->getStatus() == Screen::MOV) {
        QPoint p(ev->x() - m_movePos.x(), ev->y() - m_movePos.y());
        m_screen->move(p);
        m_movePos = ev->pos();
    }

    update();
    QWidget::mouseMoveEvent(ev);
}

void ScreenWidget::mousePressEvent(QMouseEvent *ev){
    int m_status = m_screen->getStatus();

    if (m_status == Screen::SELECT) {
        m_screen->setStart(ev->pos());
    } else if (m_status == Screen::MOV) {
        if (m_screen->isInArea(ev->pos()) == false) {
            m_screen->setStart(ev->pos());
            m_screen->setStatus(Screen::SELECT);
        } else {
            m_movePos = ev->pos();
            setCursor(Qt::SizeAllCursor);
        }
    }

    update();
    QWidget::mousePressEvent(ev);
}

void ScreenWidget::mouseReleaseEvent(QMouseEvent *ev){
    if (m_screen->getStatus() == Screen::SELECT) {
        m_screen->setStatus(Screen::MOV);
    } else if (m_screen->getStatus() == Screen::MOV) {
        this->setCursor(Qt::ArrowCursor);
    }

    repaint();
    QWidget::mouseReleaseEvent(ev);
}

void ScreenWidget::contextMenuEvent(QContextMenuEvent *){
    this->setCursor(Qt::ArrowCursor);
    m_menu->exec(cursor().pos());
}

void ScreenWidget::hideEvent(QHideEvent *event){
    qDebug() << "ScreenWidget::hideEvent called..." ;
    emit hide();
    QWidget::hideEvent(event);
}
