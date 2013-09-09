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

Circuit::Object::Object(Type _type, const QString& _label, const QString& _uuid):type(_type), label(_label), uuid(_uuid) {
}

Circuit::Object::Object(const Object& _ref): type(_ref.type), label(_ref.label), uuid(_ref.uuid) {
}

Circuit::Object::~Object() {
}

Circuit::Object& Circuit::Object::operator =(const Object& ref) {
    type = ref.type;
    label = ref.label;
    uuid = ref.uuid;
    return *this;
}

bool Circuit::Object::operator ==(const Object& ref) const {
    return type == ref.type && uuid == ref.uuid && label == ref.label;
}

bool Circuit::Object::operator !=(const Object& ref) const {
    return type != ref.type || uuid != ref.uuid || label != ref.label;
}


Circuit::Node::Node(const QString& _label):Object(Object::Node, _label), x(0.0), y(0.0), z(0.0) {
}

Circuit::Node::Node(qreal _x, qreal _y, qreal _z):Object(Object::Node), x(_x), y(_y), z(_z) {
}

Circuit::Node::Node(const QString& _label, qreal _x, qreal _y, qreal _z):Object(Object::Node, _label), x(_x), y(_y), z(_z) {
    
}

Circuit::Node::Node(const Node& _ref):Object(_ref), connectionUUIDList(_ref.connectionUUIDList), x(_ref.x), y(_ref.y), z(_ref.z) {
}

Circuit::Node::~Node() {
}

Circuit::Node& Circuit::Node::operator =(const Node& _ref) {
    connectionUUIDList = _ref.connectionUUIDList;
    x = _ref.x;
    y = _ref.y;
    z = _ref.z;
    Object::operator =(_ref);
    return *this;
}

bool Circuit::Node::operator ==(const Node& ref) const {
    return x == ref.x && y == ref.y && z == ref.z && connectionUUIDList == ref.connectionUUIDList && Object::operator ==(ref);
}

bool Circuit::Node::operator !=(const Node& ref) const {
    return x != ref.x || y != ref.y || z != ref.z || connectionUUIDList != ref.connectionUUIDList || Object::operator !=(ref);
}

Circuit::Connection::Connection(const QString& _label):Object(Object::Connection, _label) {
}

Circuit::Connection::Connection(const QString& _uuidA, const QString& _uuidB):Object(Object::Connection) {
    objectUUIDList.append(_uuidA);
    objectUUIDList.append(_uuidB);
}

Circuit::Connection::Connection(const QString& _label, const QString& _uuidA, const QString& _uuidB):Object(Object::Connection, _label) {
    objectUUIDList.append(_uuidA);
    objectUUIDList.append(_uuidB);
}

Circuit::Connection::Connection(const Connection& _ref): Object(_ref), objectUUIDList(_ref.objectUUIDList) {
}

Circuit::Connection::~Connection() {
}

Circuit::Connection& Circuit::Connection::operator =(const Connection& ref) {
    objectUUIDList = ref.objectUUIDList;
    Object::operator =(ref);
    return *this;
}

bool Circuit::Connection::operator ==(const Connection& ref) const {
    return objectUUIDList == ref.objectUUIDList && Object::operator ==(ref);
}

bool Circuit::Connection::operator !=(const Connection& ref) const {
    return objectUUIDList != ref.objectUUIDList || Object::operator !=(ref);
}


Circuit::Element::Element(Circuitling::ElementType _type, const QString& _label) : Object(Object::Element, _label), elementType(_type), x(0.0), y(0.0), z(0.0) {
}

Circuit::Element::Element(Circuitling::ElementType _type, qreal _x, qreal _y, qreal _z) : Object(Object::Element), elementType(_type), x(_x), y(_y), z(_z) {
}

Circuit::Element::Element(Circuitling::ElementType _type, const QString& _label, qreal _x, qreal _y, qreal _z):Object(Object::Element, _label), elementType(_type), x(_x), y(_y), z(_z) {
}

Circuit::Element::Element(const Element& _ref):Object(_ref), elementType(_ref.elementType), x(_ref.x), y(_ref.y), z(_ref.z), connectionUUIDList(_ref.connectionUUIDList) {
}

Circuit::Element::~Element() {
}

Circuit::Element& Circuit::Element::operator =(const Element& _ref) {
    elementType = _ref.elementType;
    x = _ref.x;
    y = _ref.y;
    z = _ref.z;
    connectionUUIDList = _ref.connectionUUIDList;
    Object::operator =(_ref);
    return *this;
}

bool Circuit::Element::operator ==(const Element& _ref) const {
    return elementType == _ref.elementType && x == _ref.x && y == _ref.y && z == _ref.z && connectionUUIDList == _ref.connectionUUIDList && Object::operator ==(_ref);
}

bool Circuit::Element::operator !=(const Element& _ref) const {
    return elementType != _ref.elementType || x != _ref.x || y != _ref.y || z != _ref.z || connectionUUIDList != _ref.connectionUUIDList || Object::operator !=(_ref);
}
