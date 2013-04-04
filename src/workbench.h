#ifndef WORKBENCH_H
#define WORKBENCH_H

#include <QObject>

class WorkbenchWidget;

class Workbench:public QObject{
	Q_OBJECT
public:
	explicit Workbench(QObject* parent = 0);
	~Workbench();

    void show();
    void close();
private:
	WorkbenchWidget* widget;
};

#endif

