// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2015 Matteo Croce

#include <QMessageBox>
#include <QProcess>
#include <QThread>

#include <vector>

#include "qdhrystone.h"

QDhrystone::QDhrystone()
{
	setupUi(this);
	connect(actionAbout, &QAction::triggered, this, &QDhrystone::about);
	connect(actionAbout_Qt, &QAction::triggered, qApp, &QApplication::aboutQt);

	connect(start, &QPushButton::clicked, this, &QDhrystone::startSlot);
	ncpu = QThread::idealThreadCount();
	if(ncpu == -1)
		ncpu = 1;
	statusbar->showMessage("Number of cores: " + QString::number(ncpu));

	// the benchmark is built in the executable, see main()
	dry = QCoreApplication::applicationFilePath();
}

void QDhrystone::startSlot()
{
	/* singlethread */
	QApplication::setOverrideCursor(Qt::WaitCursor);
	start->setEnabled(false);
	qApp->processEvents();

	QProcess proc;
	proc.start(dry, {"--dhrystone", "-b"}, QIODevice::ReadOnly);
	if(!proc.waitForStarted()) {
		statusbar->showMessage("Can't run the benchmark: " + proc.errorString());
		QApplication::restoreOverrideCursor();
		start->setEnabled(true);
		return;
	}
	proc.waitForFinished(-1);

	QString out = proc.readLine().trimmed();
	if(out == "1")
		sresult->setText(QString("%L1").arg(proc.readLine().trimmed().toInt()));
	qApp->processEvents();

	/* multithread */
	int sum = 0;

	std::vector<QProcess> procs(ncpu);
	for(int i = 0; i < ncpu; i++)
		procs[i].start(dry, {"--dhrystone", "-b"}, QIODevice::ReadOnly);

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
