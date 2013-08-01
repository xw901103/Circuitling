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

#include "workbenchgraphicsitem.h"

#include <QPen>

WorkbenchElementGraphicsItem::WorkbenchElementGraphicsItem(const QPixmap& _pixmap, QGraphicsItem* parent) : QGraphicsPixmapItem(_pixmap, parent), instance(0){
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
}

WorkbenchElementGraphicsItem::~WorkbenchElementGraphicsItem() {
    while (!connectionList.isEmpty()) {
        this->removeConnection(connectionList.first());
    }
}

QVariant WorkbenchElementGraphicsItem::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value){
    qDebug("QVariant WorkbenchElementGraphicsItem::itemChange(QGraphicsItem::GraphicsItemChange, const QVariant &) - function called");
    QVariant ret = QGraphicsPixmapItem::itemChange(change, value);
    switch (change) {
        case QGraphicsItem::ItemPositionChange:
        case QGraphicsItem::ItemPositionHasChanged:
            if(!connectionList.isEmpty())
                for (QList<WorkbenchConnectionGraphicsItem*>::iterator iter = connectionList.begin(); iter != connectionList.end(); ++iter) {
                    (*iter)->refresh();
                }
            break;
        default:
            break;
    }
    return ret;
}

void WorkbenchElementGraphicsItem:: removeConnection(WorkbenchConnectionGraphicsItem* _connection) {
    if (_connection) {
        _connection->removeConnection(this);
        if(!connectionList.isEmpty())
            connectionList.removeAll(_connection);
    }
}


WorkbenchConnectionGraphicsItem::WorkbenchConnectionGraphicsItem(WorkbenchElementGraphicsItem* _elementA, WorkbenchElementGraphicsItem* _elementB, QGraphicsItem* parent) : QGraphicsLineItem(parent), instance(0), elementA(_elementA), elementB(_elementB) {
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setPen(QPen(Qt::SolidLine));
}

WorkbenchConnectionGraphicsItem::~WorkbenchConnectionGraphicsItem() {
    if (elementA)
        elementA->removeConnection(this);
    if (elementB)
        elementB->removeConnection(this);
}

void WorkbenchConnectionGraphicsItem::removeConnection(WorkbenchElementGraphicsItem* _element) {
    if (elementA == _element)
        elementA = 0;
    if (elementB == _element)
        elementB = 0;
}

void WorkbenchConnectionGraphicsItem::setElementA(WorkbenchElementGraphicsItem* _elementA) {
    if (elementA && elementA!=_elementA) {
        elementA->removeConnection(this);
    }
    elementA = _elementA;
    if (elementA) {
        elementA->appendConnection(this);
    }
}

void WorkbenchConnectionGraphicsItem::setElementB(WorkbenchElementGraphicsItem* _elementB) {
    if (elementB && elementB!=_elementB) {
        elementB->removeConnection(this);
    }
    elementB = _elementB;
    if(elementB){
        elementB->appendConnection(this);
    }
}

void WorkbenchConnectionGraphicsItem::refresh(){
    qDebug("void WorkbenchConnectionGraphicsItem::refresh() - function called");
    QPointF posA;
    QPointF posB;
    QRectF rectA;
    QRectF rectB;
    if(elementA){
        posA = elementA->pos();
        rectA = elementA->boundingRect();
    }
    if(!elementB){
        posB = posA;
        rectB = rectA;
    }
    else{
        posB = elementB->pos();
        rectB = elementB->boundingRect();
    }
    setLine(QLineF(posA+rectA.center(), posB+rectB.center()));
    update();
}
