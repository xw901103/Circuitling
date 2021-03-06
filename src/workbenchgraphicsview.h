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

#ifndef WORKBENCHGRAPHICSVIEW_H
#define	WORKBENCHGRAPHICSVIEW_H

#include <QGraphicsView>

class QMenu;
class QAction;

class WorkbenchGraphicsView : public QGraphicsView {
    Q_OBJECT
signals:
    void sceneClicked(qreal x, qreal y);
    void itemClicked(QGraphicsItem*);
public:
    explicit WorkbenchGraphicsView(QWidget* parent = 0);
    ~WorkbenchGraphicsView();

    inline QAction* undoAction() const{return undoAct;}
    inline QAction* redoAction() const{return redoAct;}
    inline QAction* copyAction() const{return copyAct;}
    inline QAction* pasteAction() const{return pasteAct;}
    inline QAction* deleteAction() const{return deleteAct;}
    inline QAction* refreshAction() const{return refreshAct;}
    inline QAction* configureAction() const{return configureAct;}
protected:
    void drawBackground(QPainter* painter, const QRectF& rect);
    void mousePressEvent(QMouseEvent*);
private:
    QAction* undoAct;
    QAction* redoAct;
    QAction* copyAct;
    QAction* pasteAct;
    QAction* deleteAct;
    QAction* refreshAct;
    QAction* configureAct;
};

#endif
