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
, closableWindow(true)
, fileMenu(0)
, newWorkbenchAct(0)
, openFileAct(0)
, exportAct(0)
, saveAct(0)
, saveAsAct(0)
, closeWorkbenchAct(0)
, quitAct(0)
, editMenu(0)
, undoAct(0)
, redoAct(0)
, cutAct(0)
, copyAct(0)
, pasteAct(0)
, delAct(0)
, workbenchMenu(0)
, resizeAct(0)
, toolsMenu(0)
, showPrefAct(0)
, helpMenu(0)
, showAboutAct(0)
, view(0) {
    initializeMenus();

    setWindowTitle(tr("Circuitling - Workbench"));

    view = new WorkbenchGraphicsView(this);
    setCentralWidget(view);
}

WorkbenchWindow::~WorkbenchWindow() {
    if (view)
        delete view;
}

void WorkbenchWindow::initializeMenus() {
    fileMenu = new QMenu(this);
    fileMenu->setTitle(tr("File"));

    newWorkbenchAct = new QAction(this);
    newWorkbenchAct->setText(tr("New Workbench"));

    openFileAct = new QAction(this);
    openFileAct->setText(tr("Open File"));

    exportAct = new QAction(this);
    exportAct->setText(tr("Export..."));

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
    fileMenu->addSeparator();
    fileMenu->addAction(exportAct);
    fileMenu->addSeparator();    
    fileMenu->addAction(closeWorkbenchAct);
    fileMenu->addAction(quitAct);
    
    editMenu = new QMenu(this);
    editMenu->setTitle(tr("Edit"));
    
    undoAct = new QAction(this);
    undoAct->setText(tr("Undo"));
    
    redoAct = new QAction(this);
    redoAct->setText(tr("Redo"));
    
    cutAct = new QAction(this);
    cutAct->setText(tr("Cut"));

    copyAct = new QAction(this);
    copyAct->setText(tr("Copy"));
    
    pasteAct = new QAction(this);
    pasteAct->setText(tr("Paste"));
    
    delAct = new QAction(this);
    delAct->setText(tr("Delete"));
    
    editMenu->addAction(undoAct);
    editMenu->addAction(redoAct);
    editMenu->addSeparator();
    editMenu->addAction(cutAct);
    editMenu->addAction(copyAct);
    editMenu->addAction(pasteAct);
    editMenu->addAction(delAct);
    
    workbenchMenu = new QMenu(this);
    workbenchMenu->setTitle(tr("Workbench"));
    
    resizeAct = new QAction(this);
    resizeAct->setText(tr("Resize"));
    
    workbenchMenu->addAction(resizeAct);

    toolsMenu = new QMenu(this);
    toolsMenu->setTitle(tr("Tools"));

    showPrefAct = new QAction(this);
    showPrefAct->setMenuRole(QAction::PreferencesRole);
    showPrefAct->setText(tr("Preferences..."));

    toolsMenu->addAction(showPrefAct);

    helpMenu = new QMenu(this);
    helpMenu->setTitle(tr("Help"));

    showAboutAct = new QAction(this);
    showAboutAct->setMenuRole(QAction::AboutRole);
    showAboutAct->setText(tr("About"));

    helpMenu->addAction(showAboutAct);

    menuBar()->addMenu(fileMenu);
    menuBar()->addMenu(editMenu);
    menuBar()->addMenu(workbenchMenu);
    menuBar()->addMenu(toolsMenu);
    menuBar()->addMenu(helpMenu);
}

void WorkbenchWindow::closeEvent(QCloseEvent* e){
    if (e) {
        if (closableWindow) {
            e->accept();
        } else{
            closeWorkbenchAct->trigger();
            e->ignore();
        }
    }
}