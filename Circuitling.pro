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
HEADERS += src/circuit.h \
           src/global.h \
           src/circuitlingapplication.h \
           src/preferencesdialog.h \
           src/toollistwidget.h \
           src/inspectorlistwidget.h \
           src/toolboxdockwidget.h \
           src/inspectordockwidget.h \
    	   src/workbenchwindow.h \
           src/workbenchgraphicsitem.h \
           src/workbenchgraphicsscene.h \
           src/workbenchgraphicsview.h \
	       src/workbench.h
SOURCES += src/circuit.cpp \
    	   src/circuitlingapplication.cpp \
	       src/main.cpp \
           src/preferencesdialog.cpp \
           src/toollistwidget.cpp \
           src/inspectorlistwidget.cpp \
           src/toolboxdockwidget.cpp \
           src/inspectordockwidget.cpp \
    	   src/workbenchwindow.cpp \
           src/workbenchgraphicsitem.cpp \
           src/workbenchgraphicsscene.cpp \
           src/workbenchgraphicsview.cpp \
    	   src/workbench.cpp
RESOURCES += "Circuitling.qrc"
