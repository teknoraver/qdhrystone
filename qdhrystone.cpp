#include <QMessageBox>
#include <QDebug>

#include "qdhrystone.h"

QDhrystone::QDhrystone() : QMainWindow(0)
{
	setupUi(this);
	connect(actionAbout, SIGNAL(triggered()), SLOT(about()));
	connect(actionAbout_Qt, SIGNAL(triggered()), QCoreApplication::instance(), SLOT(aboutQt()));

	connect(start, SIGNAL(clicked()), SLOT(startSlot()));
}

QDhrystone::~QDhrystone()
{
}

extern "C" int dry_main (int argc, const char *argv[]);

void QDhrystone::startSlot()
{
	const char *argvs[] = {"dry", "-b"};
	const char *argvm[] = {"dry", "-b", "-t"};
	qDebug() << "start";
	dry_main(sizeof(argvs) / sizeof(argvs[0]), argvs);
	dry_main(sizeof(argvm) / sizeof(argvm[0]), argvm);
}

void QDhrystone::about()
{
	QMessageBox::about(this, "About QDhrystone", "QDhrystone - a Qt QDhrystone application<br>by Matteo Croce <a href=\"http://teknoraver.net/\">http://teknoraver.net/</a>");
}
