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
#ifndef WORKBENCHWINDOW_H
#define WORKBENCHWINDOW_H

#include <QMainWindow>

class WorkbenchGraphicsView;

class WorkbenchWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit WorkbenchWindow(QWidget* parent = 0);
    ~WorkbenchWindow();
    
    inline QAction* newWorkbenchAction() const{return newWorkbenchAct;}
    inline QAction* openFileAction() const{return openFileAct;}
    inline QAction* exportAction() const{return exportAct;}
    inline QAction* saveAction() const{return saveAct;}
    inline QAction* saveAsAction() const{return saveAsAct;}
    inline QAction* closeWorkbenchAction() const{return closeWorkbenchAct;}
    inline QAction* quitAction() const{return quitAct;}
    inline QAction* undoAction() const{return undoAct;}
    inline QAction* redoAction() const{return redoAct;}
    inline QAction* showPreferencesAction(){return showPrefAct;}
    inline QAction* showAboutAction() const{return showAboutAct;}
    inline WorkbenchGraphicsView* graphicsView() const{return view;}
private:
    void initializeMenus();
    
    QMenu* fileMenu;
    QAction* newWorkbenchAct;
    QAction* openFileAct;
    QAction* exportAct;
    QAction* saveAct;
    QAction* saveAsAct;
    QAction* closeWorkbenchAct;
    QAction* quitAct;
    QMenu* editMenu;
    QAction* undoAct;
    QAction* redoAct;
    QMenu* toolsMenu;
    QAction* showPrefAct;
    QMenu* helpMenu;
    QAction* showAboutAct;
    
    WorkbenchGraphicsView* view;
};

#endif

