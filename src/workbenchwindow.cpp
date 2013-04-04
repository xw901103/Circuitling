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
#include "workbenchwindow.h"
#include "workbenchgraphicsview.h"
#include <QtGui>

WorkbenchWindow::WorkbenchWindow(QWidget* parent) : QMainWindow(parent)
, fileMenu(0)
, newWorkbenchAct(0)
, openFileAct(0)
, saveAct(0)
, saveAsAct(0)
, closeWorkbenchAct(0)
, quitAct(0)
, helpMenu(0)
, showAboutAct(0)
, view(0)
, toolsDock(0) {
    fileMenu = new QMenu(this);
    fileMenu->setTitle(tr("File"));

    newWorkbenchAct = new QAction(this);
    newWorkbenchAct->setText(tr("New Workbench"));

    openFileAct = new QAction(this);
    openFileAct->setText(tr("Open File"));

    saveAct = new QAction(this);
    saveAct->setText(tr("Save..."));

    saveAsAct = new QAction(this);
    saveAsAct->setText(tr("Save As..."));

    closeWorkbenchAct = new QAction(this);
    closeWorkbenchAct->setText(tr("Close Workbench"));

    quitAct = new QAction(this);
    quitAct->setText(tr("Quit"));

    fileMenu->addAction(newWorkbenchAct);
    fileMenu->addAction(openFileAct);
    fileMenu->addAction(saveAct);
    fileMenu->addAction(saveAsAct);
    fileMenu->addAction(closeWorkbenchAct);
    fileMenu->addAction(quitAct);

    helpMenu = new QMenu(this);
    helpMenu->setTitle(tr("Help"));

    showAboutAct = new QAction(this);
    showAboutAct->setMenuRole(QAction::AboutRole);
    showAboutAct->setText(tr("About"));

    helpMenu->addAction(showAboutAct);

    menuBar()->addMenu(fileMenu);
    menuBar()->addMenu(helpMenu);

    setWindowTitle(tr("Circuitling - Workbench"));

    view = new WorkbenchGraphicsView(this);
    toolsDock = new QDockWidget(this);
    toolsDock->setFeatures(QDockWidget::DockWidgetFloatable | QDockWidget::DockWidgetMovable);
    toolsDock->setAllowedAreas(Qt::LeftDockWidgetArea|Qt::RightDockWidgetArea);
    addDockWidget(static_cast<Qt::DockWidgetArea>(1), toolsDock);
    setCentralWidget(view);
}

WorkbenchWindow::~WorkbenchWindow() {
    if (view)
        delete view;
}
