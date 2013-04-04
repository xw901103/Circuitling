#include "circuitling.h"
#include "mainwindow.h"

Circuitling::Circuitling(int argc, char** argv):QObject(0),app(0),mainwindow(0){
	app = new QApplication(argc, argv);
	mainwindow = new MainWindow();
}

Circuitling::~Circuitling(){
	if(app)
		delete app;
}

int Circuitling::exec(){
	if(app){
		mainwindow->show();
		return app->exec();
	}
}

void Circuitling::quit(){
	if(app)
		app->quit();
}

