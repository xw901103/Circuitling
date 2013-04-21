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
#ifndef WORKBENCHGRAPHICSITEM_H
#define	WORKBENCHGRAPHICSITEM_H

#include <QGraphicsItem>

class WorkbenchElementGraphicsItem;
class WorkbenchConnectionGraphicsItem;

class WorkbenchElementGraphicsItem : public QGraphicsPixmapItem {
    QString uuid;
//    QPixmap pixmap;
    QList<WorkbenchConnectionGraphicsItem*> connectionList;
public:
    explicit WorkbenchElementGraphicsItem(const QPixmap&, QGraphicsItem* parent = 0);
    ~WorkbenchElementGraphicsItem();
    
    inline QString getUUID() const {
        return uuid;
    }
    
    inline void setUUID(const QString& _uuid) {
        uuid = _uuid;
    }
    
    inline void appendConnection(WorkbenchConnectionGraphicsItem* _connection) {
        connectionList.append(_connection);
    }
    
    inline void removeConnection(WorkbenchConnectionGraphicsItem* _connection) {
        if(!connectionList.isEmpty())
            connectionList.removeAll(_connection);
    }
    
protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant & value);
};

class WorkbenchConnectionGraphicsItem : public QGraphicsLineItem {
    QString uuid;
    WorkbenchElementGraphicsItem* elementA;
    WorkbenchElementGraphicsItem* elementB;
public:
    explicit WorkbenchConnectionGraphicsItem(WorkbenchElementGraphicsItem* _elementA = 0, WorkbenchElementGraphicsItem* _elementB = 0, QGraphicsItem* parent = 0);
    ~WorkbenchConnectionGraphicsItem();
    
    inline QString getUUID() const {
        return uuid;
    }
    
    inline void setUUID(const QString& _uuid) {
        uuid = _uuid;
    }
    
    inline WorkbenchElementGraphicsItem* getElementA() const {
        return elementA;
    }
    
    void setElementA(WorkbenchElementGraphicsItem* _elementA);
    
    inline WorkbenchElementGraphicsItem* getElementB() const {
        return elementB;
    }
    
    void setElementB(WorkbenchElementGraphicsItem* _elementB);
    
    inline bool isValid() const{return elementA && elementB;}
    
    void refresh();
    
};

#endif
