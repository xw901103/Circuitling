######################################################################
# qmake project file
# Circuitling
# A free tool to design and simulate circuits ;)
######################################################################

TEMPLATE = app
TARGET = 
DEPENDPATH += . src
INCLUDEPATH += . src
TRANSLATIONS = 	./locale/Circuitling_en.ts \
                ./locale/Circuitling_fr.ts \
                ./locale/Circuitling_de.ts \
                ./locale/Circuitling_zh.ts \
                ./locale/Circuitling_ru.ts
QT += xml
# Input
HEADERS += src/circuit.h \
           src/circuitling.h \
           src/preferencesdialog.h \
           src/toollistwidget.h \
    	   src/workbenchwindow.h \
           src/workbenchgraphicsview.h \
	       src/workbench.h
SOURCES += src/circuit.cpp \
    	   src/circuitling.cpp \
	       src/main.cpp \
           src/preferencesdialog.cpp \
           src/toollistwidget.cpp \
    	   src/workbenchwindow.cpp \
           src/workbenchgraphicsview.cpp \
    	   src/workbench.cpp
RESOURCES += "Circuitling.qrc"
