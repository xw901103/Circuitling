#ifndef CIRCUITLING_H
#define CIRCUITLING_H

#include <QApplication>
#include <QList>

class Workbench;

class Circuitling:public QObject{
	Q_OBJECT
public:
	explicit Circuitling(int argc, char** argv);
	~Circuitling();

	int exec();
	void quit();
private:
	QApplication* app;
    QList<Workbench*> workbenchList;
};

#endif

