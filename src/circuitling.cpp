#include "circuitling.h"
#include "workbench.h"

Circuitling::Circuitling(int argc, char** argv):QObject(0),app(0){
	app = new QApplication(argc, argv);
}

Circuitling::~Circuitling(){
	if(app)
		delete app;
}

int Circuitling::exec(){
	if(app){
        workbenchList.append(new Workbench(this));
        workbenchList.at(0)->show();
        workbenchList.append(new Workbench(this));
        workbenchList.at(1)->show();
		return app->exec();
	}
    return -1;
}

void Circuitling::quit(){
	if(app)
		app->quit();
}
