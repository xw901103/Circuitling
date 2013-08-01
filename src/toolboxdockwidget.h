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

#ifndef TOOLBOXDOCKWIDGET_H
#define	TOOLBOXDOCKWIDGET_H

#include "global.h"
#include <QDockWidget>
#include <QToolButton>

class QListWidget;
class QListWidgetItem;
class ToolListWidget;

class ToolBoxDockWidget : public QDockWidget {
    Q_OBJECT
signals:
    void toolItemActivated(Circuitling::ToolItem);
    void toggledCursorMove(bool);
    void toggledCursorZoom(bool);
private slots:
    void processToolItemChange(QListWidgetItem*);
public slots:    
    void resetCursorTool();
    void resetElementTool();
public:
    explicit ToolBoxDockWidget(QWidget* parent = 0);
    ~ToolBoxDockWidget();

    Circuitling::ToolItem getCursorToolItem() const;
    void setCursorToolItem(Circuitling::ToolItem);
    
    Circuitling::ToolItem getElementToolItem() const;
    void setElementToolItem(Circuitling::ToolItem);
private:
    ToolListWidget* cursorListWidget;
    QToolButton* cursorSelectToolButton;
    QToolButton* cursorMoveToolButton;
    QToolButton* cursorConnectToolButton;
    QToolButton* cursorZoomToolButton;
//    ToolListWidget* elementListWidget;
    QListWidget* elementListWidget;
};

#endif
