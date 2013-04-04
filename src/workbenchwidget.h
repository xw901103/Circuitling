#ifndef WORKBENCHWIDGET_H
#define WORKBENCHWIDGET_H

#include <QWidget>

class WorkbenchWidget:public QWidget{
	Q_OBJECT
public:
	explicit WorkbenchWidget(QWidget* parent = 0);
	~WorkbenchWidget();
};

#endif

