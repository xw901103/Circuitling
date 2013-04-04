#include "mainwindow.h"

MainWindow::MainWindow(){
	QWidget* centralWidget = new QWidget(this);
	setCentralWidget(centralWidget);
	setWindowTitle(tr("Circuitling"));
}

MainWindow::~MainWindow(){
}
