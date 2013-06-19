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

#include "workbenchgraphicsview.h"
#include "workbenchgraphicsscene.h"
#include <QtGui>

WorkbenchGraphicsView::WorkbenchGraphicsView(QWidget* parent) : QGraphicsView(parent), 
undoAct(0), redoAct(0), copyAct(0), pasteAct(0), deleteAct(0), refreshAct(0) {
    undoAct = new QAction(this);
    undoAct->setText(tr("Undo"));
    redoAct = new QAction(this);
    redoAct->setText(tr("Redo"));
    copyAct = new QAction(this);
    copyAct->setText(tr("Copy"));
    pasteAct = new QAction(this);
    pasteAct->setText(tr("Paste"));
    deleteAct = new QAction(this);
    deleteAct->setText(tr("Delete"));
    refreshAct = new QAction(this);
    refreshAct->setText(tr("Refresh"));
    addAction(undoAct);
    addAction(redoAct);
    addAction(copyAct);
    addAction(pasteAct);
    addAction(deleteAct);
    addAction(refreshAct);
    setContextMenuPolicy(Qt::ActionsContextMenu);
    setDragMode(QGraphicsView::RubberBandDrag);

    setScene(new WorkbenchGraphicsScene(this));
    //for test reason, we set it to 800x600 with white background
    scene()->setSceneRect(0, 0, 800, 600);
//    scene()->setForegroundBrush(Qt::gray);
    scene()->setBackgroundBrush(Qt::white);
    setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    //setCacheMode(QGraphicsView::CacheNone);
//  setBackgroundBrush(Qt::NoBrush);
    scene()->addText(tr("Workbench Graphics View"), scene()->font());
    scene()->addLine(QLineF(0,0,scene()->width(),0));
    scene()->addLine(QLineF(scene()->width(),0,scene()->width(),scene()->height()));
    scene()->addLine(QLineF(0,0,0,scene()->height()));
    scene()->addLine(QLineF(0,scene()->height(),scene()->width(),scene()->height()));
//    scene()->addLine(QLineF(0,0,width(),0));
//    scene()->addRect(0,0,800,600);
}

WorkbenchGraphicsView::~WorkbenchGraphicsView() {
}

void WorkbenchGraphicsView::drawBackground(QPainter* painter, const QRectF& rect){
//     qDebug(QString("GraphicsView background x:%1 y:%2 w:%3 h:%4").arg(rect.x()).arg(rect.y()).arg(rect.width()).arg(rect.height()).toAscii());
//    Q_UNUSED(painter)
//    Q_UNUSED(rect);
//    painter->fillRect(rect, backgroundBrush());
//    if(scene())
//        scene()->drawBackground(painter, rect);
    QGraphicsView::drawBackground(painter, rect);
}

void WorkbenchGraphicsView::mousePressEvent(QMouseEvent* event) {
    if (event) {
        QGraphicsItem* item = itemAt(event->pos());
        switch (event->button()) {
            case Qt::LeftButton:
                if(item == 0){
//                    qDebug("void WorkbenchGraphicsView::mousePressEvent(QMouseEvent*) - emit sceneClicked");
                    QPointF pos(mapToScene(event->pos()));
                    emit sceneClicked(pos.x(), pos.y());
                } else {
//                    qDebug("void WorkbenchGraphicsView::mousePressEvent(QMouseEvent*) - emit itemClicked");
                    emit itemClicked(item);
                }
                break;
            case Qt::RightButton:
                break;
            default:
                break;
        }
    }
    return QGraphicsView::mousePressEvent(event);
}
