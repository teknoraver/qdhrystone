// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2015 Matteo Croce

#include <QApplication>
#include <cstring>

#include "qdhrystone.h"

// the main() of the Dhrystone benchmark, renamed at build time
extern "C" int dhrystone_main(int argc, char *argv[]);

int main(int argc, char *argv[])
{
	// the GUI runs the benchmark by launching itself with --dhrystone,
	// one process per core, as the benchmark can't run in threads
	if(argc > 1 && !strcmp(argv[1], "--dhrystone"))
		return dhrystone_main(argc - 1, argv + 1);

	QApplication a(argc, argv);
	a.setOrganizationName("QDhrystoneSoft");
	a.setApplicationName("QDhrystone");
	QDhrystone app;
	app.show();
	return a.exec();
}
