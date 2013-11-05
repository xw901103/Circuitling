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

#include "circuitdomdocumentexporter.h"
#include "circuit.h"
#include <QDomDocument>

#include <QTextStream>

CircuitDomDocumentExporter::CircuitDomDocumentExporter(QObject* parent):CircuitExporter("*.xml", parent){}

CircuitDomDocumentExporter::~CircuitDomDocumentExporter() {}

// this implementation will be re-coded.
void CircuitDomDocumentExporter::exportCircuitTo(Circuit * _circuit, QIODevice * _device) {
    if (_circuit && _device){
        QDomDocument doc;
        QDomElement rootElement = doc.createElement("xml");
        QDomElement circuitElement = doc.createElement("circuit");
        
        QDomElement circuitUUIDElement = doc.createElement("uuid");
        circuitUUIDElement.appendChild(doc.createCDATASection(_circuit->getUUID()));
        circuitElement.appendChild(circuitUUIDElement);
        
        for (QMap<QString, Circuit::Object*>::const_iterator iter = _circuit->getObjectMap().begin(); iter != _circuit->getObjectMap().end(); ++iter) {
            Circuit::Object* obj = *iter;
            QDomElement circuitObjectElement = doc.createElement("object");
            QDomElement circuitObjectUUIDElement = doc.createElement("uuid");
            QDomElement circuitObjectTypeElement = doc.createElement("type");
            circuitObjectUUIDElement.appendChild(doc.createCDATASection(obj->getUUID()));

            circuitObjectElement.appendChild(circuitObjectUUIDElement);
            circuitObjectElement.appendChild(circuitObjectTypeElement);

            QString objType("OBJECT");
            if (obj->getType() == Circuit::Object::NODE) {
                objType = "NODE";
                Circuit::Node* node = static_cast<Circuit::Node*>(obj);
                
                //coordinate
                QDomElement circuitNodeXElement = doc.createElement("x");
                QDomElement circuitNodeYElement = doc.createElement("y");
                QDomElement circuitNodeZElement = doc.createElement("z");
                circuitNodeXElement.appendChild(doc.createCDATASection(QString("%1").arg(node->getX())));
                circuitNodeYElement.appendChild(doc.createCDATASection(QString("%1").arg(node->getY())));
                circuitNodeZElement.appendChild(doc.createCDATASection(QString("%1").arg(node->getZ())));
                circuitObjectElement.appendChild(circuitNodeXElement);
                circuitObjectElement.appendChild(circuitNodeYElement);
                circuitObjectElement.appendChild(circuitNodeZElement);
                
                //connections
                QDomElement circuitNodeConnectionsElement = doc.createElement("connections");
                for(QList<QString>::const_iterator iter = node->connectionList().begin();iter != node->connectionList().end();++iter) {
                    QDomElement circuitNodeConnectionsUUIDElement = doc.createElement("uuid");
                    circuitNodeConnectionsUUIDElement.appendChild(doc.createCDATASection(*iter));
                    circuitNodeConnectionsElement.appendChild(circuitNodeConnectionsUUIDElement);
                }
                circuitObjectElement.appendChild(circuitNodeConnectionsElement);
            }
            if (obj->getType() == Circuit::Object::ELEMENT) {
                objType = "ELEMENT";
                Circuit::Element* element = static_cast<Circuit::Element*>(obj);

                //coordinate
                QDomElement circuitElementXElement = doc.createElement("x");
                QDomElement circuitElementYElement = doc.createElement("y");
                QDomElement circuitElementZElement = doc.createElement("z");
                circuitElementXElement.appendChild(doc.createCDATASection(QString("%1").arg(element->getX())));
                circuitElementYElement.appendChild(doc.createCDATASection(QString("%1").arg(element->getY())));
                circuitElementZElement.appendChild(doc.createCDATASection(QString("%1").arg(element->getZ())));
                circuitObjectElement.appendChild(circuitElementXElement);
                circuitObjectElement.appendChild(circuitElementYElement);
                circuitObjectElement.appendChild(circuitElementZElement);
                
                //connections
                QDomElement circuitElementConnectionsElement = doc.createElement("connections");
                for(QList<QString>::const_iterator iter = element->connectionList().begin();iter != element->connectionList().end();++iter) {
                    QDomElement circuitElementConnectionsUUIDElement = doc.createElement("uuid");
                    circuitElementConnectionsUUIDElement.appendChild(doc.createCDATASection(*iter));
                    circuitElementConnectionsElement.appendChild(circuitElementConnectionsUUIDElement);
                }
                circuitObjectElement.appendChild(circuitElementConnectionsElement);
            }
            if (obj->getType() == Circuit::Object::CONNECTION) {
                objType = "CONNECTION";
                Circuit::Connection* connection = static_cast<Circuit::Connection*>(obj);
                
                //objects
                QDomElement circuitConnectionObjectsElement = doc.createElement("objects");
                for(QList<QString>::const_iterator iter = connection->objectList().begin();iter != connection->objectList().end();++iter) {
                    QDomElement circuitConnectionObjectsUUIDElement = doc.createElement("uuid");
                    circuitConnectionObjectsUUIDElement.appendChild(doc.createCDATASection(*iter));
                    circuitConnectionObjectsElement.appendChild(circuitConnectionObjectsUUIDElement);
                }
                circuitObjectElement.appendChild(circuitConnectionObjectsElement);
            }
            circuitObjectTypeElement.appendChild(doc.createCDATASection(objType));
            circuitElement.appendChild(circuitObjectElement);
        }
        
        rootElement.appendChild(circuitElement);
        doc.appendChild(rootElement);

        QTextStream out(_device);
        out << doc;
    }
}
