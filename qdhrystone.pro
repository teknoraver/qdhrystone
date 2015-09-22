FORMS += qdhrystonewidget.ui
HEADERS += qdhrystone.h
SOURCES += qdhrystone.cpp main.cpp
RESOURCES += qdhrystone.qrc
QDHRYSTONE = app
CONFIG += release warn_on thread qt
TARGET = qdhrystone
QT += widgets
RC_FILE = qdhrystone.rc

win32 {
	HEADERS += dry_exe.h
}
