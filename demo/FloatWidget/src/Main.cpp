
#include <QApplication>

#ifdef Q_OS_WIN
#include "floatwidget_win.h"
#else
#include "floatwidget_linux.h"
#endif

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);


#ifdef Q_OS_WIN
	FloatWidget* floatWidget = new FloatWidget();
	floatWidget->show();
#endif

#ifdef Q_OS_LINUX
	FlaotWidget_Linux* floatWidget = new FlaotWidget_Linux();
	floatWidget->show();
#endif

	// MainWindow w;
	floatWidget->show();

	return a.exec();
}
