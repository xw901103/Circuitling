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
 * authors:Xu Waycell
 */
#include "workbench.h"
#include "circuit.h"
#include "workbenchwindow.h"
#include "circuitling.h"
#include <QAction>
#include <QMessageBox>
#include <QFileDialog>
#include <QTextStream>

Workbench::Workbench(Circuitling* parent) : QObject(static_cast<QObject*>(parent)), circuit(0), window(0) {
    circuit = new Circuit();
    window = new WorkbenchWindow();
    if(window){
        if(parent){
            connect(window->closeWorkbenchAction(), SIGNAL(triggered()), this, SLOT(close()));
            connect(this, SIGNAL(closed(Workbench*)), parent, SLOT(removeWorkbench(Workbench*)));

            connect(window->newWorkbenchAction(), SIGNAL(triggered()), parent, SLOT(createWorkbench()));
            connect(window->openFileAction(), SIGNAL(triggered()), this, SLOT(openFile()));
            connect(window->saveAction(), SIGNAL(triggered()), this, SLOT(save()));
            connect(window->saveAsAction(), SIGNAL(triggered()), this, SLOT(saveAs()));
            connect(window->quitAction(), SIGNAL(triggered()), parent, SLOT(quit()));
            connect(window->showAboutAction(), SIGNAL(triggered()), parent, SLOT(showAbout()));
        }
        window->setWindowTitle(tr("Circuitling - New Workbench"));
    }
}

Workbench::~Workbench() {
    if (window)
        delete window;
}

void Workbench::openFile() {
    QString filepath = QFileDialog::getOpenFileName(window, tr("Open file..."));
    QFile file(filepath);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(window, tr("Warning"), tr("Cannot read file.\npath:%1").arg(filepath));
        return;
    }
    if(window)
        window->setWindowTitle(tr("Circuitling - %2").arg(file.fileName()));
    file.close();
}

void Workbench::save() {
    if(!circuit)
        return;
    QString filepath = QFileDialog::getSaveFileName(window, tr("Save..."));
    QFile file(filepath);
    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::warning(window, tr("Warning"), tr("Cannot write file.\npath:%1").arg(filepath));
        return;
    }   
    QDomDocument doc = circuit->toDomDocument();
    QDomElement root = doc.documentElement();
    doc.insertBefore(doc.createComment("Created by Circuitling"), root);
    QDomElement workbench = doc.createElement("workbench");
    QDomElement workbenchWidth = doc.createElement("width");    
    QDomElement workbenchHeight = doc.createElement("height");
    //test
    workbenchWidth.appendChild(doc.createTextNode("800"));
    workbenchHeight.appendChild(doc.createTextNode("600"));

    workbench.appendChild(workbenchWidth);
    workbench.appendChild(workbenchHeight);
    root.appendChild(workbench);
    QTextStream out(&file);
    out<<doc;
    file.close();
    if(window)
        window->setWindowTitle(tr("Circuitling - %2").arg(file.fileName()));
}

void Workbench::saveAs() {
    QString filepath = QFileDialog::getSaveFileName(window, tr("Save as..."));
    QFile file(filepath);
    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::warning(window, tr("Warning"), tr("Cannot write file.\npath:%1").arg(filepath));
        return;
    }
    if(window)
        window->setWindowTitle(tr("Circuitling - %2").arg(file.fileName()));
    file.close();
}

void Workbench::show() {
    if (window)
        window->show();
}

void Workbench::close() {
    if (window){
        window->close();
        emit closed(this);
    }
}
