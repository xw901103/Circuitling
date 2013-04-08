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
#include "toollistwidget.h"
#include <QtGui>

WorkbenchWindow::WorkbenchWindow(QWidget* parent) : QMainWindow(parent)
, fileMenu(0)
, newWorkbenchAct(0)
, openFileAct(0)
, exportAct(0)
, saveAct(0)
, saveAsAct(0)
, closeWorkbenchAct(0)
, quitAct(0)
, toolsMenu(0)
, showPrefAct(0)
, helpMenu(0)
, showAboutAct(0)
, view(0)
, toolBoxDock(0) {
    initializeMenus();
    initializeToolBox();

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
    menuBar()->addMenu(toolsMenu);
    menuBar()->addMenu(helpMenu);
}

void WorkbenchWindow::initializeToolBox() {
    toolBoxDock = new QDockWidget(this);
    toolBoxDock->setWindowTitle(tr("ToolBox"));
    toolBoxDock->setFeatures(QDockWidget::DockWidgetFloatable | QDockWidget::DockWidgetMovable);
    toolBoxDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

    QWidget* toolBoxWidget = new QWidget(toolBoxDock);
    QVBoxLayout* toolBoxLayout = new QVBoxLayout(toolBoxWidget);
    toolBoxWidget->setLayout(toolBoxLayout);

    QGroupBox* cursorBox = new QGroupBox(toolBoxWidget);
    cursorBox->setTitle(tr("Cursor"));
    QVBoxLayout* cursorBoxLayout = new QVBoxLayout(cursorBox);
    cursorBox->setLayout(cursorBoxLayout);
    ToolListWidget* cursorListWidget = new ToolListWidget(toolBoxWidget);
    //cursor items for test begin
    cursorListWidget->addItem(QPixmap(":/resources/cursors/arrow.png"), tr("Select"));
    cursorListWidget->addItem(QPixmap(":/resources/cursors/hand1.png"), tr("Move"));
    cursorListWidget->addItem(QPixmap(":/resources/cursors/cross.png"), tr("Connect"));
    cursorListWidget->addItem(QPixmap(":/resources/cursors/zoom.png"), tr("Zoom"));
    //cursor items for test end
    cursorBoxLayout->addWidget(cursorListWidget);

    QGroupBox* elementBox = new QGroupBox(toolBoxWidget);
    elementBox->setTitle(tr("Element"));
    QVBoxLayout* elementBoxLayout = new QVBoxLayout(elementBox);
    elementBox->setLayout(elementBoxLayout);
    ToolListWidget* elementListWidget = new ToolListWidget(toolBoxWidget);
    //element items for test begin
    elementListWidget->addItem(QPixmap(":/resources/elements/dc_voltage_source.png"), tr("DC Voltage Source"));
    elementListWidget->addItem(QPixmap(":/resources/elements/ac_voltage_source.png"), tr("AC Voltage Source"));
    elementListWidget->addItem(QPixmap(":/resources/elements/resistor.png"), tr("Resistor"));
    elementListWidget->addItem(QPixmap(":/resources/elements/capacitor.png"), tr("Capacitor"));
    elementListWidget->addItem(QPixmap(":/resources/elements/inductor.png"), tr("Inductor"));
    elementListWidget->addItem(QPixmap(":/resources/elements/diode.png"), tr("Diode"));
    //element items for test end
    elementBoxLayout->addWidget(elementListWidget);
    
    toolBoxLayout->addWidget(cursorBox);
    toolBoxLayout->addWidget(elementBox);
    QSpacerItem* verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    toolBoxLayout->addItem(verticalSpacer);
    toolBoxDock->setWidget(toolBoxWidget);


    addDockWidget(static_cast<Qt::DockWidgetArea> (1), toolBoxDock);
}