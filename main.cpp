#include <QApplication>
#include <QDesktopWidget>
#include "qdhrystone.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	a.setOrganizationName("QDhrystoneSoft");
	a.setApplicationName("QDhrystone");
	QDhrystone app;
	app.move((QApplication::desktop()->screenGeometry(&app).width() - app.width()) / 2, (QApplication::desktop()->screenGeometry(&app).height() - app.height()) / 2);
	app.setVisible(true);
	return a.exec();
}
