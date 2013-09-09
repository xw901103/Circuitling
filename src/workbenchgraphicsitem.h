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

#ifndef WORKBENCHGRAPHICSITEM_H
#define	WORKBENCHGRAPHICSITEM_H

#include "global.h"
#include <QGraphicsItem>
#include "circuit.h"

/**
 * Root class of all workbench circuit graphics items
 */
class WorkbenchGraphicsItem : public QGraphicsItem {
    DISABLE_COPY(WorkbenchGraphicsItem) //no copy construct allowed
public:
    enum ItemType {
        Unknow = UserType + 1,
        Node,
        Connection,
        Element
    };
    explicit WorkbenchGraphicsItem(ItemType _type = Unknow, const QString& _uuid = QString(), QGraphicsItem* parent = 0);
    virtual ~WorkbenchGraphicsItem() = 0;
    
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0) = 0;
    virtual QRectF boundingRect() const = 0;

    inline virtual int type() const {
        return itemType;
    }
    
    inline QString getUuid() const {
        return uuid;
    }
    inline void setUuid(const QString& _uuid) {
        uuid = _uuid;
    }
private:
    QString uuid;
    ItemType itemType;
};

class WorkbenchNodeGraphicsItem;
class WorkbenchConnectionGraphicsItem;
class WorkbenchElementGraphicsItem;

/**
 * Workbench circuit node graphics item
 */
class WorkbenchNodeGraphicsItem:public WorkbenchGraphicsItem {
    DISABLE_COPY(WorkbenchNodeGraphicsItem) //no copy construct allowed
public:
    explicit WorkbenchNodeGraphicsItem(QGraphicsItem* parent = 0);
    ~WorkbenchNodeGraphicsItem();
};

/**
 * Workbench circuit connection graphics item
 */
//this class will be redesigned. this class will draw a line between two graphics items.
class WorkbenchConnectionGraphicsItem : public QGraphicsLineItem {
    QString uuid;
    Circuit::Connection* instance; //point to a existing connection
    WorkbenchElementGraphicsItem* elementA;
    WorkbenchElementGraphicsItem* elementB;
    DISABLE_COPY(WorkbenchConnectionGraphicsItem) //no copy construct allowed
public:
    explicit WorkbenchConnectionGraphicsItem(WorkbenchElementGraphicsItem* _elementA = 0, WorkbenchElementGraphicsItem* _elementB = 0, QGraphicsItem* parent = 0);
    ~WorkbenchConnectionGraphicsItem();
    
    inline Circuit::Connection* getInstance() const{return instance;}
    inline void setInstance(Circuit::Connection* _instance){
        instance = _instance;
        if(instance)
            uuid = instance->getUUID();
    }
    
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
    
    void removeConnection(WorkbenchElementGraphicsItem* _element);
    
};

/**
 * Workbench circuit element graphics item
 */
class WorkbenchElementGraphicsItem : public QGraphicsPixmapItem {
    QString uuid;
    //    QPixmap pixmap;
    Circuit::Element* instance;
    QList<WorkbenchConnectionGraphicsItem*> connectionList;
    
    DISABLE_COPY(WorkbenchElementGraphicsItem) //no copy construct allowed
public:
    explicit WorkbenchElementGraphicsItem(const QPixmap&, QGraphicsItem* parent = 0);
    ~WorkbenchElementGraphicsItem();
    
    inline Circuit::Element* getInstance() const{return instance;}
    inline void setInstance(Circuit::Element* _instance){
        instance = _instance;
        if(instance)
            uuid = instance->getUUID();
    }
    
    inline QString getUUID() const {
        return uuid;
    }
    
    inline void setUUID(const QString& _uuid) {
        uuid = _uuid;
    }
    
    inline void appendConnection(WorkbenchConnectionGraphicsItem* _connection) {
        connectionList.append(_connection);
    }
    
    void removeConnection(WorkbenchConnectionGraphicsItem* _connection);
protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant & value);
};

#endif
