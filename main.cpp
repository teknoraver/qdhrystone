// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2015 Matteo Croce

#include <QApplication>
#include "qdhrystone.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	a.setOrganizationName("QDhrystoneSoft");
	a.setApplicationName("QDhrystone");
	QDhrystone app;
	app.show();
	return a.exec();
}
