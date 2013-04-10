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
#ifndef TOOLLISTWIDGET_H
#define	TOOLLISTWIDGET_H

#include "global.h"
#include <QListWidget>

class ToolListWidget;

class ToolListItem : public QListWidgetItem {
public:
    explicit ToolListItem(const QPixmap& icon, const QString& toolTip, ToolListWidget* parent = 0);
    ~ToolListItem();

    inline Circuitling::ToolType getToolType() const {
        return toolType;
    }

    inline void setToolType(Circuitling::ToolType _type) {
        toolType = _type;
    }

    inline Circuitling::ToolItem getToolItem() const {
        return toolItem;
    }

    inline void setToolItem(Circuitling::ToolItem _item) {
        toolItem = _item;
    }
private:
    Circuitling::ToolType toolType;
    Circuitling::ToolItem toolItem;
};

class ToolListWidget : public QListWidget {
    Q_OBJECT
public:
    explicit ToolListWidget(QWidget* parent);
    virtual ~ToolListWidget();

    void addItem(ToolListItem*);
};

#endif
