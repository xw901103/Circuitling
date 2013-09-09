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

#include <QAction>
#include <QMessageBox>
#include <QFileDialog>
#include <QTextStream>

#include "workbench.h"
#include "circuitlingapplication.h"
#include "circuit.h"
#include "workbenchwindow.h"
#include "circuitelementconfigurationdialog.h"
#include "toolboxdockwidget.h"
#include "inspectordockwidget.h"
#include "workbenchgraphicsitem.h"
#include "workbenchgraphicsscene.h"
#include "workbenchgraphicsview.h"
#include "toolboxdockwidget.h"
//test reason
#include <QGraphicsPixmapItem>

Workbench::Workbench(CircuitlingApplication* parent) : QObject(static_cast<QObject*> (parent)), closing(false), circuit(0), window(0), confDialog(0), toolBoxDock(0), inspectorDock(0), currentConnectionItem(0) {
    circuit = new Circuit();
    window = new WorkbenchWindow();
    initializeDocks();
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
            connect(window->deleteAction(), SIGNAL(triggered()), this, SLOT(deleteSelectedItems()));
            connect(window->configureAction(), SIGNAL(triggered()), this, SLOT(showCurrentCircuitElementConfiguration()));
            connect(window->showPreferencesAction(), SIGNAL(triggered()), parent, SLOT(showPreferences()));
            connect(window->showAboutAction(), SIGNAL(triggered()), parent, SLOT(showAbout()));
            
            connect(window->graphicsView(), SIGNAL(sceneClicked(qreal, qreal)), this, SLOT(addItemToScene(qreal, qreal)));
            connect(window->graphicsView(), SIGNAL(itemClicked(QGraphicsItem*)), this, SLOT(processClickedItem(QGraphicsItem*)));
            connect(window->graphicsView()->deleteAction(), SIGNAL(triggered()), this, SLOT(deleteSelectedItems()));
        }
        window->setClosableWindow(false);
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
        window->setWindowTitle(tr("Circuitling - %1").arg(file.fileName()));
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
//    QDomDocument doc = circuit->toDomDocument();
/*
    QDomDocument doc = CircuitDomDocumentParser::parseCircuitToDomDocument(circuit);
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
        window->setWindowTitle(tr("Circuitling - %1").arg(file.fileName()));
 */
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
        window->setWindowTitle(tr("Circuitling - %1").arg(file.fileName()));
    file.close();
}

void Workbench::show() {
    if (window){
        window->setClosableWindow(false);
        window->show();
    }
}

void Workbench::close() {
    if (window) {
        window->setClosableWindow(false);
        if(QMessageBox::warning(window, tr("Warning"), tr("Are you sure that all your works have been saved?"), QMessageBox::Ok|QMessageBox::Cancel, QMessageBox::Cancel) == QMessageBox::Ok){
            closing = true;
            window->setClosableWindow(true);
            window->close();
            emit closed(this);
        }
    }
}

void Workbench::addItemToScene(qreal x, qreal y) {
    if (window) {
        QGraphicsItem* item = 0;
        WorkbenchElementGraphicsItem* workbenchItem = 0;
        QString uuid;
        if(toolBoxDock->getCursorToolItem() == Circuitling::ConnectCursor && currentConnectionItem){
            //connect two element together
        } else {
            switch (toolBoxDock->getElementToolItem()) {
                case Circuitling::SelectCursor:
                case Circuitling::ConnectCursor:
                case Circuitling::MoveCursor:
                case Circuitling::ZoomCursor:
                case Circuitling::UnknowItem:
                    break;
                case Circuitling::NodeElement:
                    workbenchItem = new WorkbenchElementGraphicsItem(QPixmap(":/resources/elements/node.png"));
                    uuid = circuit->addElement(Circuit::Element(Circuitling::Node, x, y));
                    break;
                case Circuitling::DC_VoltageSourceElement:
                    workbenchItem = new WorkbenchElementGraphicsItem(QPixmap(":/resources/elements/dc_voltage_source.png"));
                    uuid = circuit->addElement(Circuit::Element(Circuitling::DC_VoltageSource, x, y));
                    break;
                case Circuitling::AC_VoltageSourceElement:
                    workbenchItem = new WorkbenchElementGraphicsItem(QPixmap(":/resources/elements/ac_voltage_source.png"));
                    uuid = circuit->addElement(Circuit::Element(Circuitling::AC_VoltageSource, x, y));
                    break;
                case Circuitling::ResistorElement:
                    workbenchItem = new WorkbenchElementGraphicsItem(QPixmap(":/resources/elements/resistor.png"));
                    uuid = circuit->addElement(Circuit::Element(Circuitling::Resistor, x, y));
                    break;
                case Circuitling::CapacitorElement:
                    workbenchItem = new WorkbenchElementGraphicsItem(QPixmap(":/resources/elements/capacitor.png"));
                    uuid = circuit->addElement(Circuit::Element(Circuitling::Capacitor, x, y));
                    break;
                case Circuitling::InductorElement:
                    workbenchItem = new WorkbenchElementGraphicsItem(QPixmap(":/resources/elements/inductor.png"));
                    uuid = circuit->addElement(Circuit::Element(Circuitling::Inductor, x, y));
                    break;
                case Circuitling::DiodeElement:
                    workbenchItem = new WorkbenchElementGraphicsItem(QPixmap(":/resources/elements/diode.png"));
                    uuid = circuit->addElement(Circuit::Element(Circuitling::Diode, x, y));
                    break;
            }
        }
        if(workbenchItem) {
            workbenchItem->setInstance(circuit->getElement(uuid));
            item = static_cast<QGraphicsItem*>(workbenchItem);
            WorkbenchGraphicsScene* scene = static_cast<WorkbenchGraphicsScene*>(window->graphicsView()->scene());
            if(scene)
                scene->registerItem(uuid, item);
        }
        if (item) {
            window->graphicsView()->scene()->addItem(item);
            QRectF itemRect = item->boundingRect();
            item->setPos(QPointF(x, y)-itemRect.center());
            item->setFlag(QGraphicsItem::ItemIsSelectable, true);
            item->setFlag(QGraphicsItem::ItemIsMovable, true);
            item->setToolTip(uuid);
            if(inspectorDock){
                inspectorDock->appendObject(uuid);
            }
        }
    }
}

// remove selected item from scene and circuit
/** HAVE NOT DONE YET !!! **/
void Workbench::deleteSelectedItems() {
    qDebug("void Workbench::deleteSelectedItems() called");
    if (window)
        if (window->graphicsView())
            if (window->graphicsView()->scene()) {
                WorkbenchGraphicsScene* scene = static_cast<WorkbenchGraphicsScene*>(window->graphicsView()->scene());
                QList<QGraphicsItem*> items(scene->selectedItems());
                for (QList<QGraphicsItem*>::iterator iter = items.begin(); iter != items.end(); ++iter) {
                    QString uuid(scene->getUUIDByItem(*iter));
                    qDebug("Delete circuit object %s", uuid.toAscii().data());
                    if (circuit)
                        circuit->deleteObject(uuid);
                    if (inspectorDock)
                        inspectorDock->removeObject(uuid);
                    scene->removeItem(*iter);
                }
            }
}

void Workbench::activateTool(Circuitling::ToolItem toolItem) {
    if(toolItem != Circuitling::ConnectCursor)
        if (currentConnectionItem)
            if(!currentConnectionItem->isValid()){
                window->graphicsView()->scene()->removeItem(currentConnectionItem);
//                if(inspectorDock)
//                    inspectorDock->removeObject(currentConnectionItem->getUUID());
                delete currentConnectionItem;
                currentConnectionItem = 0;
            }
    bool resetElementTool = false;
    bool resetCursorTool = false;
    switch(toolItem){
        case Circuitling::SelectCursor:
//            toolBoxDock->resetElementTool();
            resetElementTool = true;
//            currentConnectionItem = 0;
            break;
        case Circuitling::ConnectCursor:
            if(!currentConnectionItem){
                window->graphicsView()->scene()->clearSelection();
                currentConnectionItem = new WorkbenchConnectionGraphicsItem();
//                currentConnectionItem->setLine(0,0, 50, 50);
                window->graphicsView()->scene()->addItem(currentConnectionItem);
//                if(inspectorDock)
//                    inspectorDock->appendObject(currentConnectionItem->getUUID());
            }
            resetElementTool = true;
            break;
        case Circuitling::MoveCursor:
            currentConnectionItem = 0;
            resetElementTool = true;
            break;
        case Circuitling::ZoomCursor:
            currentConnectionItem = 0;
            resetElementTool = true;
            break;
        case Circuitling::NodeElement:
        case Circuitling::DC_VoltageSourceElement:
        case Circuitling::AC_VoltageSourceElement:
        case Circuitling::ResistorElement:
        case Circuitling::InductorElement:
        case Circuitling::CapacitorElement:
        case Circuitling::DiodeElement:
            resetCursorTool = true;
            break;
        default:
            qDebug("void Workbench::activateTool(Circuitling::ToolItem) - default case");
            break;
    }
    if(resetElementTool)
        toolBoxDock->resetElementTool();
    if(resetCursorTool)
        toolBoxDock->resetCursorTool();
}

void Workbench::processClickedItem(QGraphicsItem * item){
    if(item){
        if(toolBoxDock->getCursorToolItem() == Circuitling::ConnectCursor){
            if(!currentConnectionItem){
                currentConnectionItem = new WorkbenchConnectionGraphicsItem();
                window->graphicsView()->scene()->addItem(currentConnectionItem);                
            }
            if(!currentConnectionItem->getElementA()){
                qDebug("void Workbench::processClickedItem(QGraphicsItem*) - add element A to connection");
                currentConnectionItem->setElementA(static_cast<WorkbenchElementGraphicsItem*>(item));
//                currentConnectionItem->setLine(QLineF(item->pos(), item->pos()));
                currentConnectionItem->refresh();
            } else if (!currentConnectionItem->getElementB()){
                qDebug("void Workbench::processClickedItem(QGraphicsItem*) - add element B to connection");
                currentConnectionItem->setElementB(static_cast<WorkbenchElementGraphicsItem*>(item));
//                currentConnectionItem->setLine(QLineF(currentConnectionItem->getElementA()->pos(),item->pos()));
                currentConnectionItem->refresh();
                QString uuid = circuit->addConnection(Circuit::Connection(currentConnectionItem->getElementA()->getUUID(), currentConnectionItem->getElementB()->getUUID()));
                currentConnectionItem->setInstance(circuit->getConnection(uuid));
                currentConnectionItem->setToolTip(uuid);
                WorkbenchGraphicsScene* scene = static_cast<WorkbenchGraphicsScene*>(window->graphicsView()->scene());
                if(scene){
                    scene->registerItem(uuid, currentConnectionItem);
                }
                if(inspectorDock)
                    inspectorDock->appendObject(uuid);
                currentConnectionItem = 0; //connection is done
            }
        }
    }
}

void Workbench::initializeDocks() {
    toolBoxDock = new ToolBoxDockWidget(window);
    if (toolBoxDock) {
        toolBoxDock->resetCursorTool();
        toolBoxDock->resetElementTool();
        connect(toolBoxDock, SIGNAL(toggledCursorMove(bool)), this, SLOT(toggleCursorMove(bool)));
        connect(toolBoxDock, SIGNAL(toggledCursorZoom(bool)), this, SLOT(toggleCursorZoom(bool)));
        connect(toolBoxDock, SIGNAL(toolItemActivated(Circuitling::ToolItem)), this, SLOT(activateTool(Circuitling::ToolItem)));
    }
    
    inspectorDock = new InspectorDockWidget(window);
    if(inspectorDock)
        connect(inspectorDock, SIGNAL(itemSelected(const QString&)), this, SLOT(inspectSceneItem(const QString&)));
    
    if (window){
        window->addDockWidget(static_cast<Qt::DockWidgetArea> (1), toolBoxDock);
        window->addDockWidget(static_cast<Qt::DockWidgetArea> (1), inspectorDock);
    }
}

void Workbench::inspectSceneItem(const QString & uuid){
    qDebug("void Workbench::inspectSceneItem(const QString&) - called");
    WorkbenchGraphicsScene* scene = static_cast<WorkbenchGraphicsScene*>(window->graphicsView()->scene());
    if(scene){
        scene->clearFocus();
        scene->clearSelection();
        QGraphicsItem* item = scene->getItemByUUID(uuid);
        if(item)
            item->setSelected(true);
    }
}

void Workbench::toggleCursorMove(bool _status) {
    qDebug("void Workbench::toggleCursorMove - called ARGUMENT:%d", _status);
}

void Workbench::toggleCursorZoom(bool _status) {
    qDebug("void Workbench::toggleCursorZoom - called ARGUMENT:%d", _status);
}

void Workbench::showCurrentCircuitElementConfiguration() {
    if (!confDialog)
        confDialog = new CircuitElementConfigurationDialog(this->window);
    confDialog->exec();
}
