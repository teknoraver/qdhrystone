#include <QMessageBox>
#include <QTemporaryFile>
#include <QDir>
#include <QProcess>
#include <QThread>
#include <QDebug>

#include "qdhrystone.h"

#ifdef Q_OS_WINDOW
#include "dry_exe.h"
#endif

QDhrystone::QDhrystone() : dry("dry")
{
	setupUi(this);
	connect(actionAbout, SIGNAL(triggered()), SLOT(about()));
	connect(actionAbout_Qt, SIGNAL(triggered()), QCoreApplication::instance(), SLOT(aboutQt()));

	connect(start, SIGNAL(clicked()), SLOT(startSlot()));
	ncpu = QThread::idealThreadCount();
	if(ncpu == -1)
		ncpu = 1;
	statusbar->showMessage("Number of cores: " + QString::number(ncpu));

#ifdef Q_OS_WINDOW
	QTemporaryFile *dry_file = new QTemporaryFile(QDir::tempPath() + "/dry-XXXXXX.exe", this);
	dry_file->open();
	dry_file->write(dry_exe, sizeof(dry_exe));
	dry_file->close();
	dry = dry_file->fileName();
#endif
}

QDhrystone::~QDhrystone()
{
}

void QDhrystone::startSlot()
{
	/* singlethread */
	QApplication::setOverrideCursor(Qt::WaitCursor);
	start->setEnabled(false);
	qApp->processEvents();

	QProcess proc;
	proc.start(dry, QStringList() << "-b", QIODevice::ReadOnly);
	proc.waitForFinished(-1);

	QString out = proc.readAllStandardOutput();
	QStringList outs = out.split('\n', QString::SkipEmptyParts);
	if(outs[0] == "1")
		sresult->setText(QString("%L1").arg(outs[1].toInt()));
	qApp->processEvents();

	/* multithread */
	int sum = 0;

	QProcess procs[ncpu];
	for(int i = 0; i < ncpu; i++)
		procs[i].start(dry, QStringList() << "-b", QIODevice::ReadOnly);

	for(int i = 0; i < ncpu; i++)
		procs[i].waitForFinished(-1);

	for(int i = 0; i < ncpu; i++) {
		QString out = procs[i].readAllStandardOutput();
		QStringList outs = out.split('\n', QString::SkipEmptyParts);
		if(outs[0] == "1")
			sum += outs[1].toInt();
	}

	mresult->setText(QString("%L1").arg(sum));

	QApplication::restoreOverrideCursor();
	QApplication::restoreOverrideCursor();
	start->setEnabled(true);
}

void QDhrystone::about()
{
	QMessageBox::about(this, "About QDhrystone", "QDhrystone - a Qt QDhrystone application<br>by Matteo Croce <a href=\"http://teknoraver.net/\">http://teknoraver.net/</a>");
}
