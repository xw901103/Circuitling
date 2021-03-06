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

#include "toolboxdockwidget.h"
#include "toollistwidget.h"
#include <QtGui>

ToolBoxDockWidget::ToolBoxDockWidget(QWidget* parent) : QDockWidget(parent) {
    setWindowTitle(tr("ToolBox"));
    setFeatures(QDockWidget::DockWidgetFloatable | QDockWidget::DockWidgetMovable);
    setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    
    QWidget* toolBoxWidget = new QWidget(this);
    QVBoxLayout* toolBoxLayout = new QVBoxLayout(toolBoxWidget);
    toolBoxWidget->setLayout(toolBoxLayout);
    
    QGroupBox* cursorBox = new QGroupBox(toolBoxWidget);
    cursorBox->setTitle(tr("Cursor"));
    QVBoxLayout* cursorBoxLayout = new QVBoxLayout(cursorBox);
    cursorBox->setLayout(cursorBoxLayout);
//    cursorListWidget = new ToolListWidget(toolBoxWidget);
    //cursor items for test begin
    /*
    ToolListItem* cursorItem = 0;
    cursorItem = new ToolListItem(QPixmap(":/resources/cursors/arrow.png"), tr("Select"), cursorListWidget);
    cursorItem->setToolType(Circuitling::Cursor);
    cursorItem->setToolItem(Circuitling::SelectCursor);
    cursorListWidget->addItem(cursorItem);
    cursorItem = new ToolListItem(QPixmap(":/resources/cursors/hand1.png"), tr("Move"), cursorListWidget);
    cursorItem->setToolType(Circuitling::Cursor);
    cursorItem->setToolItem(Circuitling::MoveCursor);
    cursorListWidget->addItem(cursorItem);
    cursorItem = new ToolListItem(QPixmap(":/resources/cursors/cross.png"), tr("Connect"), cursorListWidget);
    cursorItem->setToolType(Circuitling::Cursor);
    cursorItem->setToolItem(Circuitling::ConnectCursor);
    cursorListWidget->addItem(cursorItem);
    cursorItem = new ToolListItem(QPixmap(":/resources/cursors/zoom.png"), tr("Zoom"), cursorListWidget);
    cursorItem->setToolType(Circuitling::Cursor);
    cursorItem->setToolItem(Circuitling::ZoomCursor);
    cursorListWidget->addItem(cursorItem);
    */
    //cursor items for test end
    
    //cursor tool buttons
    QHBoxLayout* cursorToolButtonGroupLayout = new QHBoxLayout(this);
    cursorSelectToolButton = new QToolButton(this);
    cursorSelectToolButton->setText(tr("Select"));
    cursorSelectToolButton->setToolTip(tr("Select"));
    cursorSelectToolButton->setIcon(QIcon(QPixmap(":/resources/cursors/arrow.png")));
    cursorSelectToolButton->setCheckable(true);
    cursorSelectToolButton->setAutoExclusive(true);
    connect(cursorSelectToolButton, SIGNAL(clicked()), this, SLOT(resetElementTool()));
    cursorToolButtonGroupLayout->addWidget(cursorSelectToolButton);
    cursorConnectToolButton = new QToolButton(this);
    cursorConnectToolButton->setText(tr("Connect"));
    cursorConnectToolButton->setToolTip(tr("Connect"));
    cursorConnectToolButton->setIcon(QIcon(QPixmap(":/resources/cursors/cross.png")));
    cursorConnectToolButton->setCheckable(true);
    cursorConnectToolButton->setAutoExclusive(true);
    connect(cursorConnectToolButton, SIGNAL(clicked()), this, SLOT(resetElementTool()));
    cursorToolButtonGroupLayout->addWidget(cursorConnectToolButton);
    cursorMoveToolButton = new QToolButton(this);
    cursorMoveToolButton->setText(tr("Move"));
    cursorMoveToolButton->setToolTip(tr("Move"));
    cursorMoveToolButton->setIcon(QIcon(QPixmap(":/resources/cursors/hand1.png")));
    cursorMoveToolButton->setCheckable(true);
    connect(cursorMoveToolButton, SIGNAL(toggled(bool)), this, SIGNAL(toggledCursorMove(bool)));
    cursorToolButtonGroupLayout->addWidget(cursorMoveToolButton);
    cursorZoomToolButton = new QToolButton(this);
    cursorZoomToolButton->setText(tr("Zoom"));
    cursorZoomToolButton->setToolTip(tr("Zoom"));
    cursorZoomToolButton->setIcon(QIcon(QPixmap(":/resources/cursors/zoom.png")));
    cursorZoomToolButton->setCheckable(true);
    connect(cursorZoomToolButton, SIGNAL(toggled(bool)), this, SIGNAL(toggledCursorZoom(bool)));
    cursorToolButtonGroupLayout->addWidget(cursorZoomToolButton);
    QSpacerItem* cursorToolButtonGroupHSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    cursorToolButtonGroupLayout->addItem(cursorToolButtonGroupHSpacer);
    cursorBoxLayout->addLayout(cursorToolButtonGroupLayout);
    QSpacerItem* cursorBoxVSpacer = new QSpacerItem(20, 206, QSizePolicy::Minimum, QSizePolicy::Expanding);
    cursorBoxLayout->addItem(cursorBoxVSpacer);
    
//    QToolButton* cursorTestButton = new QToolButton(this);
//    cursorTestButton->setCheckable(true);
//    cursorTestButton->setIcon(QIcon(QPixmap(":/resources/cursors/hand1.png")));
//    cursorTestButton->setText(tr("Test"));
//    cursorBoxLayout->addWidget(cursorTestButton);
//    cursorBoxLayout->addWidget(cursorListWidget);
    
    QGroupBox* elementBox = new QGroupBox(toolBoxWidget);
    elementBox->setTitle(tr("Element"));
    QVBoxLayout* elementBoxLayout = new QVBoxLayout(elementBox);
    elementBox->setLayout(elementBoxLayout);
//    elementListWidget = new ToolListWidget(toolBoxWidget);
    elementListWidget = new QListWidget(toolBoxWidget);
    //element items for test begin
    ToolListItem* elementItem = 0;
    elementItem = new ToolListItem(QPixmap(":/resources/elements/node"), tr("Node"), elementListWidget);
    elementItem->setToolType(Circuitling::Element);
    elementItem->setToolItem(Circuitling::NodeElement);
    elementListWidget->addItem(elementItem);
    elementItem = new ToolListItem(QPixmap(":/resources/elements/dc_voltage_source.png"), tr("DC Voltage Source"), elementListWidget);
    elementItem->setToolType(Circuitling::Element);
    elementItem->setToolItem(Circuitling::DC_VoltageSourceElement);
    elementListWidget->addItem(elementItem);
    elementItem = new ToolListItem(QPixmap(":/resources/elements/ac_voltage_source.png"), tr("AC Voltage Source"), elementListWidget);
    elementItem->setToolType(Circuitling::Element);
    elementItem->setToolItem(Circuitling::AC_VoltageSourceElement);
    elementListWidget->addItem(elementItem);
    elementItem = new ToolListItem(QPixmap(":/resources/elements/resistor.png"), tr("Resistor"), elementListWidget);
    elementItem->setToolType(Circuitling::Element);
    elementItem->setToolItem(Circuitling::ResistorElement);
    elementListWidget->addItem(elementItem);
    elementItem = new ToolListItem(QPixmap(":/resources/elements/capacitor.png"), tr("Capacitor"), elementListWidget);
    elementItem->setToolType(Circuitling::Element);
    elementItem->setToolItem(Circuitling::CapacitorElement);
    elementListWidget->addItem(elementItem);
    elementItem = new ToolListItem(QPixmap(":/resources/elements/inductor.png"), tr("Inductor"), elementListWidget);
    elementItem->setToolType(Circuitling::Element);
    elementItem->setToolItem(Circuitling::InductorElement);
    elementListWidget->addItem(elementItem);
    elementItem = new ToolListItem(QPixmap(":/resources/elements/diode.png"), tr("Diode"), elementListWidget);
    elementItem->setToolType(Circuitling::Element);
    elementItem->setToolItem(Circuitling::DiodeElement);
    elementListWidget->addItem(elementItem);
    //element items for test end
    elementBoxLayout->addWidget(elementListWidget);
    
    toolBoxLayout->addWidget(cursorBox);
    toolBoxLayout->addWidget(elementBox);
    QSpacerItem* verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    toolBoxLayout->addItem(verticalSpacer);
    setWidget(toolBoxWidget);
    
//    connect(cursorListWidget, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(processToolItemChange(QListWidgetItem*)));
    connect(elementListWidget, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(processToolItemChange(QListWidgetItem*)));
}

ToolBoxDockWidget::~ToolBoxDockWidget() {
}

void ToolBoxDockWidget::resetCursorTool(){
//    if (cursorListWidget)
//        cursorListWidget->reset();
    if (cursorSelectToolButton)
        cursorSelectToolButton->setChecked(true);
    if (cursorConnectToolButton)
        cursorConnectToolButton->setChecked(false);
    if (cursorMoveToolButton)
        cursorMoveToolButton->setChecked(true);
    if (cursorZoomToolButton)
        cursorZoomToolButton->setChecked(false);
}

void ToolBoxDockWidget::resetElementTool(){
    if (elementListWidget)
        elementListWidget->reset();
}

Circuitling::ToolItem ToolBoxDockWidget::getCursorToolItem() const{
/*
    if(cursorListWidget){
        ToolListItem* item = static_cast<ToolListItem*>(cursorListWidget->currentItem());
        if(item){
            return item->getToolItem();
        }
    }
    return Circuitling::UnknowItem;
*/
    if (cursorSelectToolButton)
        if (cursorSelectToolButton->isChecked())
            return Circuitling::SelectCursor;
    if (cursorConnectToolButton)
        if (cursorConnectToolButton->isChecked())
            return Circuitling::ConnectCursor;
    return Circuitling::UnknowItem;
}

Circuitling::ToolItem ToolBoxDockWidget::getElementToolItem() const{
    if(elementListWidget){
        ToolListItem* item = static_cast<ToolListItem*>(elementListWidget->currentItem());
        if(item){
            return item->getToolItem();
        }
    }
    return Circuitling::UnknowItem;
}

void ToolBoxDockWidget::processToolItemChange(QListWidgetItem* item){
    if(item){
        ToolListItem* toolItem = static_cast<ToolListItem*>(item);
        emit toolItemActivated(toolItem->getToolItem());
    }
}