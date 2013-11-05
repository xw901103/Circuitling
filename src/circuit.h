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

#ifndef CIRCUIT_H
#define CIRCUIT_H

#include "global.h"
#include <QString>
#include <QMap>

/**
 * Circuitling circuit class
 */
class Circuit {
    DISABLE_COPY(Circuit) //no copy construct allowed
public:
    class Object;
    class Node;
    class Connection;
    class Element;

    Circuit();
    ~Circuit();
    
    const QMap<QString, Object*>& getObjectMap() const;
    
    Object* getObject(const QString& uuid) const;
    void deleteObject(const QString& uuid);
    
    Node* getNode(const QString& uuid) const;
    /**
     * add an new node then return its uuid.
     * @param _node node
     * @return uuid of this node in the circuit
     */
    QString addNode(const Node& _node);
    void deleteNode(const QString& uuid);
    

    Element* getElement(const QString& uuid) const;
    /**
     * add an new element then return its uuid.
     * @param _element element
     * @return uuid of this element in the circuit
     */
    QString addElement(const Element& _element);
    void deleteElement(const QString& uuid);

    Connection* getConnection(const QString& uuid) const;
    /**
     * add an new connection then return its uuid.
     * @param _connection connection
     * @return uuid of this element in the circuit
     */
    QString addConnection(const Connection& _connection);
    void deleteConnection(const QString& uuid);

    /**
     * if there does not have one then generate one
     */
    QString getUUID();

    inline void setUUID(const QString& _uuid) {
        uuid = _uuid;
    }

    inline QString getTitle() const {
        return title;
    }

    inline void setTitle(const QString& _title) {
        title = _title;
    }

private:
    QMap<QString, Object*> objectMap;
    QString uuid;
    QString title;
};

/**
 * Root class of all Circuitling circuit components
 */
class Circuit::Object {
public:
    enum Type {
        UNKNOW,
        NODE,
        ELEMENT,
        CONNECTION
    };
    explicit Object(Type _type = UNKNOW, const QString& _label = QString(), const QString& _uuid = QString());
    Object(const Object&);
    virtual ~Object() =0;
    
    inline Type getType() const{return type;}
    inline void setType(Type _type){type = _type;}
    
    inline const QString& getLabel() const{return label;}
    inline void setLabel(const QString& _label){label = _label;}
    
    inline const QString& getUUID() const{return uuid;}
    inline void setUUID(const QString& _uuid){uuid = _uuid;}
    
    Object& operator =(const Object& ref);
    
    bool operator ==(const Object& ref) const;
    bool operator !=(const Object& ref) const;
private:
    Type type;
    QString label;
    QString uuid;
};

/**
 * Circuitling circuit node class
 */
class Circuit::Node:public Object {
    QList<QString> connectionUUIDList;
    qreal x;
    qreal y;
    qreal z;
public:
    explicit Node(const QString& _label = QString());
    explicit Node(qreal _x, qreal _y, qreal _z = 0);
    explicit Node(const QString& _label, qreal _x, qreal _y, qreal _z = 0);
    Node(const Node&);
    ~Node();
    
    inline void appendConnection(const QString& _uuid) {
        connectionUUIDList.append(_uuid);
    }
    
    inline void removeConnection(const QString& _uuid) {
        connectionUUIDList.removeAll(_uuid);
    }
    
    inline const QList<QString>& connectionList() const{
        return connectionUUIDList;
    }
    
    inline qreal getX() const {
        return x;
    }
    
    inline qreal getY() const {
        return y;
    }
    
    inline qreal getZ() const {
        return z;
    }
    
    inline void locate(qreal _x, qreal _y, qreal _z = 0) {
        x = _x;
        y = _y;
        z = _z;
    }
    
    Node& operator =(const Node& ref);
    
    bool operator ==(const Node& ref) const;
    bool operator !=(const Node& ref) const;
};

/**
 * Circuitling circuit connection class. it store a connection between two circuit objects.
 * NOTE: the object has been stored should not be a connection. otherwise, the functionalities of other application components would be undefined.
 */
class Circuit::Connection:public Object{
    QList<QString> objectUUIDList;
public:
    explicit Connection(const QString& _label = QString());
    explicit Connection(const QString& _uuidA, const QString& _uuidB);
    explicit Connection(const QString& _label, const QString& _uuidA, const QString& _uuidB);
    Connection(const Connection&);
    ~Connection();
    
    inline const QList<QString>& objectList() const{
        return objectUUIDList;
    }
    
    /**
     * Clear stored object uuids in the list.
     */
    inline void clear() {
        objectUUIDList.clear();
    }
    
    inline void appendObject(const QString& _uuid) {
        objectUUIDList.append(_uuid);
    }
    
    inline void removeObject(const QString& _uuid) {
        objectUUIDList.removeAll(_uuid);
    }
    
    inline bool isValid() const{
        return !objectUUIDList.isEmpty() && objectUUIDList.size() > 1;
    }
    
    Connection& operator =(const Connection& ref);
    
    bool operator ==(const Connection& ref) const;
    bool operator !=(const Connection& ref) const;
};

/**
 * Circuitling circuit element class
 */
class Circuit::Element:public Object {
    Circuitling::ElementType elementType;
    qreal x;
    qreal y;
    qreal z;
    QList<QString> connectionUUIDList;
public:
    explicit Element(Circuitling::ElementType _type, const QString& _label = QString());
    explicit Element(Circuitling::ElementType _type, qreal _x, qreal _y, qreal _z = 0);
    explicit Element(Circuitling::ElementType _type, const QString& _label, qreal _x, qreal _y, qreal _z = 0);
    Element(const Element&);
    ~Element();
    
    inline Circuitling::ElementType getElementType() const {
        return elementType;
    }
    
    inline void setElementType(Circuitling::ElementType _type) {
        elementType = _type;
    }
    
    inline void appendConnection(const QString& _uuid) {
        connectionUUIDList.append(_uuid);
    }
    
    inline void removeConnection(const QString& _uuid) {
        connectionUUIDList.removeAll(_uuid);
    }
    
    inline const QList<QString>& connectionList() const{
        return connectionUUIDList;
    }
    
    inline qreal getX() const {
        return x;
    }
    
    inline qreal getY() const {
        return y;
    }
    
    inline qreal getZ() const {
        return z;
    }
    
    inline void locate(qreal _x, qreal _y, qreal _z = 0) {
        x = _x;
        y = _y;
        z = _z;
    }
    
    Element& operator =(const Element&);
    bool operator ==(const Element&) const;
    bool operator !=(const Element&) const;
};

#endif

