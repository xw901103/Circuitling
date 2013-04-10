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
#ifndef WORKBENCHGRAPHICSSCENE_H
#define	WORKBENCHGRAPHICSSCENE_H

#include "global.h"
#include <QGraphicsScene>
#include <QGraphicsItem>

class WorkbenchConnectionGraphicsItem;

class WorkbenchElementGraphicsItem : public QGraphicsItem {
    QString uuid;
    QList<WorkbenchConnectionGraphicsItem*> connectionList;
public:
    explicit WorkbenchElementGraphicsItem(QGraphicsItem* parent = 0);
    ~WorkbenchElementGraphicsItem();

    inline QString getUUID() const {
        return uuid;
    }

    inline void setUUID(const QString& _uuid) {
        uuid = _uuid;
    }
    
    inline void appendConnection(WorkbenchConnectionGraphicsItem* _connection){connectionList.append(_connection);}
    inline void removeConnection(WorkbenchConnectionGraphicsItem* _connection){connectionList.removeAll(_connection);}
};

class WorkbenchConnectionGraphicsItem : public QGraphicsItem {
    QString uuid;
    WorkbenchElementGraphicsItem* elementA;
    WorkbenchElementGraphicsItem* elementB;    
public:
    explicit WorkbenchConnectionGraphicsItem(WorkbenchElementGraphicsItem* _elementA, WorkbenchElementGraphicsItem* _elementB, QGraphicsItem* parent = 0);
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

    inline void setElementA(WorkbenchElementGraphicsItem* _elementA) {
        elementA = _elementA;
    }

    inline WorkbenchElementGraphicsItem* getElementB() const {
        return elementA;
    }

    inline void setElementB(WorkbenchElementGraphicsItem* _elementB) {
        elementB = _elementB;
    }

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = 0);
};

class WorkbenchGraphicsScene : public QGraphicsScene {
    Q_OBJECT
public:
    explicit WorkbenchGraphicsScene(QObject* parent = 0);
    ~WorkbenchGraphicsScene();

    void addElement(WorkbenchElementGraphicsItem*, qreal x, qreal y);
    void addConnection(WorkbenchConnectionGraphicsItem*);
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent*);
};

#endif
