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
#include "circuitlingapplication.h"
#include "circuit.h"
#include "workbenchwindow.h"
#include <QAction>
#include <QMessageBox>
#include <QFileDialog>
#include <QTextStream>
#include "workbenchgraphicsview.h"
#include "toolboxdockwidget.h"
//test reason
#include <QGraphicsPixmapItem>

Workbench::Workbench(CircuitlingApplication* parent) : QObject(static_cast<QObject*> (parent)), circuit(0), window(0) {
    circuit = new Circuit();
    window = new WorkbenchWindow();
    if (window) {
        if (parent) {
            connect(window->closeWorkbenchAction(), SIGNAL(triggered()), this, SLOT(close()));
            connect(this, SIGNAL(closed(Workbench*)), parent, SLOT(removeWorkbench(Workbench*)));

            connect(window->newWorkbenchAction(), SIGNAL(triggered()), parent, SLOT(createWorkbench()));
            connect(window->openFileAction(), SIGNAL(triggered()), this, SLOT(openFile()));
            connect(window->exportAction(), SIGNAL(triggered()), this, SLOT(exportTo()));
            connect(window->saveAction(), SIGNAL(triggered()), this, SLOT(save()));
            connect(window->saveAsAction(), SIGNAL(triggered()), this, SLOT(saveAs()));
            connect(window->quitAction(), SIGNAL(triggered()), parent, SLOT(quit()));
            connect(window->showPreferencesAction(), SIGNAL(triggered()), parent, SLOT(showPreferences()));
            connect(window->showAboutAction(), SIGNAL(triggered()), parent, SLOT(showAbout()));

            connect(window->graphicsView(), SIGNAL(sceneClicked(qreal, qreal)), this, SLOT(addItemToScene(qreal, qreal)));
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
    if (filepath.isEmpty())
        return;
    QFile file(filepath);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(window, tr("Warning"), tr("Cannot read file.\npath:%1").arg(filepath));
        return;
    }
    if (window)
        window->setWindowTitle(tr("Circuitling - %2").arg(file.fileName()));
    file.close();
}

void Workbench::exportTo() {
    if (!circuit)
        return;
    QString filepath = QFileDialog::getSaveFileName(window, tr("Export..."));
    if (filepath.isEmpty())
        return;
    QFile file(filepath);
    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::warning(window, tr("Warning"), tr("Cannot write file.\npath:%1").arg(filepath));
        return;
    }

    QGraphicsScene* currentScene = window->graphicsView()->scene();
    QPixmap pixmap(currentScene->width(), currentScene->height());
    QPainter exportPainter(&pixmap);
    currentScene->render(&exportPainter);
    exportPainter.end();
    pixmap.save(&file, "PNG");
    file.close();
}

void Workbench::save() {
    if (!circuit)
        return;
    QString filepath = QFileDialog::getSaveFileName(window, tr("Save..."));
    if (filepath.isEmpty())
        return;
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
    out << doc;
    file.close();
    if (window)
        window->setWindowTitle(tr("Circuitling - %2").arg(file.fileName()));
}

void Workbench::saveAs() {
    QString filepath = QFileDialog::getSaveFileName(window, tr("Save as..."));
    if (filepath.isEmpty())
        return;
    QFile file(filepath);
    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::warning(window, tr("Warning"), tr("Cannot write file.\npath:%1").arg(filepath));
        return;
    }
    if (window)
        window->setWindowTitle(tr("Circuitling - %2").arg(file.fileName()));
    file.close();
}

void Workbench::show() {
    if (window)
        window->show();
}

void Workbench::close() {
    if (window) {
        window->close();
        emit closed(this);
    }
}

void Workbench::addItemToScene(qreal x, qreal y) {
    if (window) {
        QGraphicsItem* item = 0;
        QString uuid;
        switch (window->toolBox()->getElementToolItem()) {
            case Circuitling::SelectCursor:
            case Circuitling::ConnectCursor:
            case Circuitling::MoveCursor:
            case Circuitling::ZoomCursor:
            case Circuitling::UnknowItem:
                break;
            case Circuitling::NodeElement:
                break;
            case Circuitling::DC_VoltageSourceElement:
//                item = window->graphicsView()->scene()->addLine(0,0,x,y);
                item = window->graphicsView()->scene()->addPixmap(QPixmap(":/resources/elements/dc_voltage_source.png"));
                uuid = circuit->addElement(Circuit::Element(x, y, Circuitling::DC_VoltageSource));
                break;
            case Circuitling::AC_VoltageSourceElement:
                item = window->graphicsView()->scene()->addPixmap(QPixmap(":/resources/elements/ac_voltage_source.png"));
                uuid = circuit->addElement(Circuit::Element(x, y, Circuitling::AC_VoltageSource));
                break;
            case Circuitling::ResistorElement:
                item = window->graphicsView()->scene()->addPixmap(QPixmap(":/resources/elements/resistor.png"));
                uuid = circuit->addElement(Circuit::Element(x, y, Circuitling::Resistor));
                break;
            case Circuitling::CapacitorElement:
                item = window->graphicsView()->scene()->addPixmap(QPixmap(":/resources/elements/capacitor.png"));
                uuid = circuit->addElement(Circuit::Element(x, y, Circuitling::Capacitor));
                break;
            case Circuitling::InductorElement:
                item = window->graphicsView()->scene()->addPixmap(QPixmap(":/resources/elements/inductor.png"));
                uuid = circuit->addElement(Circuit::Element(x, y, Circuitling::Inductor));
                break;
            case Circuitling::DiodeElement:
                item = window->graphicsView()->scene()->addPixmap(QPixmap(":/resources/elements/diode.png"));
                uuid = circuit->addElement(Circuit::Element(x, y, Circuitling::Diode));
                break;
        }
        if (item){
            item->setPos(x, y);
            item->setToolTip(uuid);
        }
    }
}
