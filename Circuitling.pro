######################################################################
# qmake project file
# Circuitling
# A free tool to design and simulate circuits ;)
######################################################################

TEMPLATE = app
TARGET = 
DEPENDPATH += . src
INCLUDEPATH += . src
TRANSLATIONS = 	locale/Circuitling_en.ts \
                locale/Circuitling_fr.ts \
                locale/Circuitling_de.ts \
                locale/Circuitling_zh.ts \
                locale/Circuitling_ru.ts
QT += xml
# Input
HEADERS += \
# global head
           src/global.h \
# circuit classes
           src/circuit.h \
# circuitling classes
           src/circuitlingapplication.h \
# circuitling dialogs
           src/preferencesdialog.h \
# importer/exporter
           src/circuitimporter.h \
	       src/circuitexporter.h \
# dom importer/exporter
           src/circuitdomdocumentimporter.h \
           src/circuitdomdocumentexporter.h \
# workbench classes
           src/workbench.h \
    	   src/workbenchwindow.h \
# workbench dialogs
      	   src/circuitelementconfigurationdialog.h \
# workbench graphics view
           src/workbenchgraphicsitem.h \
           src/workbenchgraphicsscene.h \
           src/workbenchgraphicsview.h \
# workbench docks
           src/toollistwidget.h \
           src/toolboxdockwidget.h \
           src/inspectorlistwidget.h \
           src/inspectordockwidget.h

SOURCES += \
# main entry
	   src/main.cpp \
# circuit classes
	   src/circuit.cpp \
# circuitling classes
	   src/circuitlingapplication.cpp \
# circuitling dialogs
           src/preferencesdialog.cpp \
# importer/exporter
	   src/circuitimporter.cpp \
	   src/circuitexporter.cpp \
# dom importer/exporter
	   src/circuitdomdocumentimporter.cpp \
	   src/circuitdomdocumentexporter.cpp \
# workbench classes
    	   src/workbench.cpp \
    	   src/workbenchwindow.cpp \
# workbench dialogs
      	   src/circuitelementconfigurationdialog.cpp \
# workbench graphics view
           src/workbenchgraphicsitem.cpp \
           src/workbenchgraphicsscene.cpp \
           src/workbenchgraphicsview.cpp \
# workbench docks
           src/toollistwidget.cpp \
           src/toolboxdockwidget.cpp \
           src/inspectorlistwidget.cpp \
           src/inspectordockwidget.cpp
RESOURCES += "Circuitling.qrc"
