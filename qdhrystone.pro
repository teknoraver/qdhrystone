FORMS += qdhrystonewidget.ui
HEADERS += qdhrystone.h
SOURCES += qdhrystone.cpp main.cpp dry1.c dry2.c
RESOURCES += qdhrystone.qrc
QDHRYSTONE = app
CONFIG += release warn_on thread qt
TARGET = qdhrystone
QT += widgets
RC_FILE = qdhrystone.rc
QMAKE_CFLAGS += -O3
