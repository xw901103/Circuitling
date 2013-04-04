#include "workbench.h"
#include "workbenchwidget.h"

Workbench::Workbench(QObject* parent):QObject(parent), widget(0){
    widget = new WorkbenchWidget();
}

Workbench::~Workbench(){
	if(widget)
		delete widget;
}

void Workbench::show(){
    if(widget)
        widget->show();
}
void Workbench::close(){
    if(widget)
        widget->close();
}

