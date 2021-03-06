/**
 * Circuitling
 * 
 * Copyright (c) 2013, Circuitling Project
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met: 
 * 
 * 1. Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer. 
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution. 
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 * The views and conclusions contained in the software and documentation are those
 * of the authors and should not be interpreted as representing official policies, 
 * either expressed or implied, of the Circuitling Project.
 * 
 * authors:Xu Waycell [xw901103@gmail.com]
 */

#include "circuitlingapplication.h"
#include "preferencesdialog.h"
#include "workbench.h"

#include "circuitdomdocumentimporter.h"
#include "circuitdomdocumentexporter.h"

#include <QDesktopServices>
#include <QDir>
#include <QMessageBox>

CircuitlingApplication::CircuitlingApplication(int argc, char** argv) : QObject(0), app(0), prefDialog(0), exporter(0), importer(0) {
    app = new QApplication(argc, argv);
}

CircuitlingApplication::~CircuitlingApplication() {
//DO NOT DESTROY QApplication OBJECT
//    if (app)
//        delete app;
    for (QList<CircuitImporter*>::Iterator iter = importerList.begin(); iter != importerList.end(); ++iter)
        delete *iter;
    for (QList<CircuitExporter*>::Iterator iter = exporterList.begin(); iter != exporterList.end(); ++iter)
        delete *iter;
}

bool CircuitlingApplication::initialize(){
    QDir dir;
    if(dir.mkpath(getApplicationDataPath())){
        
        exporter = new CircuitDomDocumentExporter(this);
        importer = new CircuitDomDocumentImporter(this);
        
        importerList.append(importer);
        exporterList.append(exporter);
        
        return true;
    }
    return false;
}

CircuitExporter* CircuitlingApplication::getCircuitExporter() const {
    return exporter;
}

CircuitImporter* CircuitlingApplication::getCircuitImporter() const {
    return importer;
}

const QList<CircuitExporter*>& CircuitlingApplication::getCircuitExporterList() const{
    return exporterList;
}
const QList<CircuitImporter*>& CircuitlingApplication::getCircuitImporterList() const{
    return importerList;
}


void CircuitlingApplication::createWorkbench() {
    Workbench* workbench = new Workbench(this);
    workbenchList.append(workbench);
    workbench->show();
}

void CircuitlingApplication::removeWorkbench(Workbench* workbench){
    if(workbench){
        if(workbenchList.removeOne(workbench)){
            if(!workbench->isClosing())
                workbench->close();
            delete workbench;
        }
    }
}

int CircuitlingApplication::exec() {
    if (app && initialize()) {
        createWorkbench();
        return app->exec();
    }
    QMessageBox::critical(0, tr("Circuitling"), tr("Circuitling cannot finish initialization."));
    return -1;
}

void CircuitlingApplication::quit() {
    if (app)
        app->quit();
}

QString CircuitlingApplication::getApplicationDataPath() const{
    return QString("%1/Circuitling").arg(QDesktopServices::storageLocation(QDesktopServices::DataLocation));
}

void CircuitlingApplication::showPreferences(){
    if(!prefDialog)
        prefDialog = new PreferencesDialog();
    prefDialog->exec();
}

void CircuitlingApplication::showAbout(){
    QMessageBox::about(0, tr("About"), tr("Circuitling\nA free tool to design and simulate circuits ;)\nCreated by Xu Waycell [xw901103@gmail.com]"));
}