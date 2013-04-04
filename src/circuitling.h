#ifndef CIRCUITLING_H
#define CIRCUITLING_H

#include <QApplication>

class MainWindow;

class Circuitling:public QObject{
	Q_OBJECT
public:
	explicit Circuitling(int argc, char** argv);
	~Circuitling();

	int exec();
	void quit();
private:
	QApplication* app;
	MainWindow* mainwindow;
};

#endif

