#include <QMessageBox>
#include <QDir>
#include <QProcess>
#include <QRandomGenerator>
#include <QThread>

#include <vector>

#include "qdhrystone.h"

#ifdef Q_OS_WIN32
#include "dry_exe.h"
#endif

QDhrystone::QDhrystone() : dry("dry")
{
	setupUi(this);
	connect(actionAbout, &QAction::triggered, this, &QDhrystone::about);
	connect(actionAbout_Qt, &QAction::triggered, qApp, &QApplication::aboutQt);

	connect(start, &QPushButton::clicked, this, &QDhrystone::startSlot);
	ncpu = QThread::idealThreadCount();
	if(ncpu == -1)
		ncpu = 1;
	statusbar->showMessage("Number of cores: " + QString::number(ncpu));

#ifdef Q_OS_WIN32
	dry = QDir::tempPath() + "/dry-" + QString::number(QRandomGenerator::global()->generate()) + ".exe";
	QFile dry_file(dry);
	if(dry_file.open(QIODevice::WriteOnly)) {
		dry_file.write(dry_exe, sizeof(dry_exe));
		dry_file.close();
	}
#endif
}

QDhrystone::~QDhrystone()
{
#ifdef Q_OS_WIN32
	QFile::remove(dry);
#endif
}

void QDhrystone::startSlot()
{
	/* singlethread */
	QApplication::setOverrideCursor(Qt::WaitCursor);
	start->setEnabled(false);
	qApp->processEvents();

	QProcess proc;
	proc.start(dry, {"-b"}, QIODevice::ReadOnly);
	proc.waitForFinished(-1);

	QString out = proc.readLine().trimmed();
	if(out == "1")
		sresult->setText(QString("%L1").arg(proc.readLine().trimmed().toInt()));
	qApp->processEvents();

	/* multithread */
	int sum = 0;

	std::vector<QProcess> procs(ncpu);
	for(int i = 0; i < ncpu; i++)
		procs[i].start(dry, {"-b"}, QIODevice::ReadOnly);

	for(int i = 0; i < ncpu; i++)
		procs[i].waitForFinished(-1);

	for(int i = 0; i < ncpu; i++) {
		out = procs[i].readLine().trimmed();
		if(out == "1")
			sum += procs[i].readLine().trimmed().toInt();
	}

	mresult->setText(QString("%L1").arg(sum));

	QApplication::restoreOverrideCursor();
	start->setEnabled(true);
}

void QDhrystone::about()
{
	QMessageBox::about(this, "About QDhrystone", "QDhrystone - a Qt QDhrystone application<br>by Matteo Croce <a href=\"https://matteocroce.it/\">https://matteocroce.it/</a>");
}
