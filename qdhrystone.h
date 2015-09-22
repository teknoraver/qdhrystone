#ifndef QDHRYSTONE_H
#define QDHRYSTONE_H

#include <QMainWindow>

#include "ui_qdhrystonewidget.h"

class QDhrystone: public QMainWindow, private Ui::MainWindow
{
	Q_OBJECT
public:
	QDhrystone();
	~QDhrystone();
private:
	QString dry;
	int ncpu;
private slots:
	void startSlot();
	void about();
};

#endif
