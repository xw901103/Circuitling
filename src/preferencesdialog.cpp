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

#include "preferencesdialog.h"
#include <QVBoxLayout>
#include <QTabWidget>
#include <QDialogButtonBox>

#include <QGroupBox>
#include <QFormLayout>
#include <QLabel>
#include <QToolButton>

#include <QFileDialog>

class GeneralPage:public QWidget{
public:
    explicit GeneralPage(QWidget* parent = 0);
    ~GeneralPage();
};

GeneralPage::GeneralPage(QWidget* parent):QWidget(parent){}

GeneralPage::~GeneralPage(){}

WorkbenchPage::WorkbenchPage(QWidget* parent):QWidget(parent), uComboBox(0), wSpinBox(0), hSpinBox(0), pLineEdit(0){
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    setLayout(mainLayout);

    QGroupBox* defaultSizeGroupBox = new QGroupBox(tr("Default Size"), this);
    QFormLayout* defaultSizeLayout = new QFormLayout(defaultSizeGroupBox);
    defaultSizeGroupBox->setLayout(defaultSizeLayout);
    QLabel* uLabel = new QLabel(tr("Unit:"), this);
    QLabel* wLabel = new QLabel(tr("Width:"), this);
    QLabel* hLabel = new QLabel(tr("Height:"), this);
    uComboBox = new QComboBox(this);
    uComboBox->addItem(tr("Pixel"));
    uComboBox->addItem(tr("Millimeter"));
    uComboBox->addItem(tr("Centimeter"));
    uComboBox->addItem(tr("Meter"));
    uComboBox->addItem(tr("Inch"));
    connect(uComboBox, SIGNAL(activated(const QString&)), this, SLOT(setWorkbenchSizeUnitSuffix(const QString&)));
    wSpinBox = new QSpinBox(this);
    hSpinBox = new QSpinBox(this);
    defaultSizeLayout->setWidget(0, QFormLayout::LabelRole, uLabel);
    defaultSizeLayout->setWidget(0, QFormLayout::FieldRole, uComboBox);
    defaultSizeLayout->setWidget(1, QFormLayout::LabelRole, wLabel);
    defaultSizeLayout->setWidget(1, QFormLayout::FieldRole, wSpinBox);
    defaultSizeLayout->setWidget(2, QFormLayout::LabelRole, hLabel);
    defaultSizeLayout->setWidget(2, QFormLayout::FieldRole, hSpinBox);
    
    mainLayout->addWidget(defaultSizeGroupBox);
    
    QGroupBox* autosaveGroupBox = new QGroupBox(tr("Autosave"), this);
    autosaveGroupBox->setCheckable(true);
    QFormLayout* autosaveLayout = new QFormLayout(autosaveGroupBox);
    autosaveGroupBox->setLayout(autosaveLayout);
    QLabel* pLabel = new QLabel(tr("Path:"), this);
    pLineEdit = new QLineEdit(this);
    QToolButton* pToolButton = new QToolButton(this);
    pToolButton->setText(tr("..."));
    connect(pToolButton, SIGNAL(clicked()), this, SLOT(getAutosavePath()));
    QHBoxLayout* pLayout = new QHBoxLayout();
    pLayout->addWidget(pLineEdit);
    pLayout->addWidget(pToolButton);
    autosaveLayout->setWidget(0, QFormLayout::LabelRole, pLabel);
    autosaveLayout->setLayout(0, QFormLayout::FieldRole, pLayout);
//    autosaveLayout->setWidget(0, QFormLayout::FieldRole, pLineEdit);
    
    mainLayout->addWidget(autosaveGroupBox);
}

WorkbenchPage::~WorkbenchPage(){}

void WorkbenchPage::setWorkbenchSizeUnitSuffix(const QString& unit){
    if(wSpinBox || hSpinBox){
        QString suffix;
        if(unit == "Pixel")
            suffix = QString("px");
        else if(unit == "Millimeter")
            suffix = QString("mm");
        else if(unit == "Centimeter")
            suffix = QString("cm");
        else if(unit == "Meter")
            suffix = QString("m");
        else if(unit == "Inch")
            suffix = QString("\"");
        if(wSpinBox)
            wSpinBox->setSuffix(suffix);
        if(hSpinBox)
            hSpinBox->setSuffix(suffix);
    }
}

void WorkbenchPage::getAutosavePath(){
    QString path = QFileDialog::getExistingDirectory();
    if(pLineEdit)
        pLineEdit->setText(path);
}

PreferencesDialog::PreferencesDialog(QWidget* parent):QDialog(parent){
    setWindowTitle(tr("Preferences"));
    
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    setLayout(mainLayout);
    
    GeneralPage* generalPage = new GeneralPage(this);
    WorkbenchPage* workbenchPage = new WorkbenchPage(this);
    
    QTabWidget* tabWidget = new QTabWidget(this);
    tabWidget->addTab(generalPage, tr("General"));
    tabWidget->addTab(workbenchPage, tr("Workbench"));
    
    QDialogButtonBox* buttonBox = new QDialogButtonBox(this);
    buttonBox->setStandardButtons(QDialogButtonBox::Apply|QDialogButtonBox::Cancel|QDialogButtonBox::RestoreDefaults);
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    
    mainLayout->addWidget(tabWidget);
    mainLayout->addWidget(buttonBox);
}

PreferencesDialog::~PreferencesDialog(){}
