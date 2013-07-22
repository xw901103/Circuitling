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

#include "circuit.h"
#include "global.h"
#include <QUuid>

Circuit::Circuit() {
}

Circuit::~Circuit() {
}

QString Circuit::getUUID() {
    if (uuid.isEmpty())
        uuid = QUuid::createUuid();
    return uuid; //it will cast to QString
}

/*
QDomDocument Circuit::toDomDocument() {
    QDomDocument doc;
    QDomElement root = doc.createElement("xml");
    QDomElement circuit = doc.createElement("circuit");
    QDomElement circuitUUID = doc.createElement("uuid");
    circuitUUID.appendChild(doc.createCDATASection(getUUID()));
    circuit.appendChild(circuitUUID);

//    for (QMap<QString, Element>::const_iterator iter = elementMap.begin(); iter != elementMap.end(); ++iter) {
//        QDomElement element = doc.createElement("element");

//        QDomElement elementX = doc.createElement("x");
//        elementX.appendChild(doc.createTextNode("0"));
//        QDomElement elementY = doc.createElement("y");
//        elementY.appendChild(doc.createTextNode("0"));
        //coordinate tags
//        element.appendChild(elementX);
//        element.appendChild(elementY);

//        circuit.appendChild(element);
//    }
 
    root.appendChild(circuit);
    doc.appendChild(root);
    return doc;
}
*/

Circuit::Object* Circuit::getObject(const QString& _uuid) const{
    QMap<QString, Object*>::const_iterator iter = objectMap.find(_uuid);
    if (iter != objectMap.end())
        return *iter;
    return 0;
}

void Circuit::deleteObject(const QString & _uuid) {
    QMap<QString, Object*>::iterator iter = objectMap.find(_uuid);
    if (iter != objectMap.end()) {
        delete (*iter);
        objectMap.erase(iter);
    }
}

Circuit::Element* Circuit::getElement(const QString& _uuid) const {
    Object* obj = getObject(_uuid);
    if (obj)
        if (obj->getType() == Object::Element)
            return static_cast<Element*>(obj);
    return 0;
}

QString Circuit::addElement(const Element& _element) {
    Object* obj = static_cast<Object*>(new Element(_element));
    QMap<QString, Object*>::iterator iter = objectMap.insert(QUuid::createUuid(), obj);
    (*iter)->setUUID(iter.key());
    return iter.key();
}

void Circuit::deleteElement(const QString& _uuid) {
    QMap<QString, Object*>::iterator iter = objectMap.find(_uuid);
    if (iter != objectMap.end())
        if ((*iter)->getType() == Object::Element) {
            delete (*iter);
            objectMap.erase(iter);
        }
}

Circuit::Connection* Circuit::getConnection(const QString& _uuid) const {
    Object* obj = getObject(_uuid);
    if (obj)
        if (obj->getType() == Object::Connection)
            return static_cast<Connection*>(obj);
    return 0;
}

QString Circuit::addConnection(const Connection& _connection) {
    Object* obj = static_cast<Object*>(new Connection(_connection));
    QMap<QString, Object*>::iterator iter = objectMap.insert(QUuid::createUuid(), obj);
    (*iter)->setUUID(iter.key());
    return iter.key();
}

void Circuit::deleteConnection(const QString& _uuid) {
    QMap<QString, Object*>::iterator iter = objectMap.find(_uuid);
    if (iter != objectMap.end())
        if ((*iter)->getType() == Object::Connection) {
            delete (*iter);
            objectMap.erase(iter);
        }
}

Circuit::Object::~Object(){}

Circuit::Element::Element(Circuitling::ElementType _type) : Object(Object::Element), elementType(_type), x(0.0), y(0.0) {
}

Circuit::Element::Element(const QString& _label, Circuitling::ElementType _type) : Object(Object::Element, _label), elementType(_type), x(0.0), y(0.0) {
}

Circuit::Element::Element(qreal _x, qreal _y, Circuitling::ElementType _type) : Object(Object::Element), elementType(_type), x(_x), y(_y) {
}

Circuit::Element::Element(const Element& _ref) : Object(_ref), elementType(_ref.elementType), x(_ref.x), y(_ref.y) {
}

Circuit::Element::~Element() {
}

Circuit::Element& Circuit::Element::operator =(const Element& _ref) {
    Object::operator=(_ref);
    elementType = _ref.elementType;
    x = _ref.x;
    y = _ref.y;
    return *this;
}

bool Circuit::Element::operator ==(const Element& _ref) const {
    return Object::operator==(_ref) && elementType == _ref.elementType && x == _ref.x && y == _ref.y;
}

bool Circuit::Element::operator !=(const Element& _ref) const {
    return Object::operator!=(_ref) || elementType != _ref.elementType || x != _ref.x || y != _ref.y;
}

Circuit::Connection::Connection(class Element* a, class Element* b) : Object(Object::Connection), elementA(a), elementB(b) {
}

Circuit::Connection::Connection(const Connection& _ref) : Object(_ref), elementA(_ref.elementA), elementB(_ref.elementB) {
}

Circuit::Connection::~Connection() {
}

Circuit::Connection& Circuit::Connection::operator =(const Connection& _ref) {
    Object::operator=(_ref);
    elementA = _ref.elementA;
    elementB = _ref.elementB;
    return *this;
}

bool Circuit::Connection::operator ==(const Connection& _ref) const {
    return Object::operator==(_ref) && elementA == _ref.elementA && elementB == _ref.elementB;
}

bool Circuit::Connection::operator !=(const Connection& _ref) const {
    return Object::operator!=(_ref) || elementA != _ref.elementA || elementB != _ref.elementB;
}
