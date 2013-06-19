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
#include <QDomDocument>

class Circuit {
public:
    class Object;
    class Element;
    class Connection;

    Circuit();
    ~Circuit();
    
    Object* getObject(const QString& uuid) const;
    void deleteObject(const QString& uuid);

    Element* getElement(const QString& uuid) const;
    /**
     * add a new element then return its uuid.
     * @param _element element
     * @return uuid of this element in the circuit
     */
    QString addElement(const Element& _element);
    void deleteElement(const QString& _uuid);

    Connection* getConnection(const QString& uuid) const;
    /**
     * add a new connection then return its uuid.
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

    QDomDocument toDomDocument();
private:
//    QMap<QString, Element> elementMap;
//    QMap<QString, Connection> connectionMap;
    QMap<QString, Object*> objectMap;
    QString uuid;
    QString title;
//    qreal x;
//    qreal y;
};

class Circuit::Object {
public:
    enum Type {
        Unknow,
        Element,
        Connection
    };
    explicit Object(Type _type, const QString& _label = QString(), const QString& _uuid = QString()):type(_type), label(_label), uuid(_uuid){}
    Object(const Object& _ref): type(_ref.type), label(_ref.label), uuid(_ref.uuid) {}
    virtual ~Object() =0;
    
    inline Type getType() const{return type;}
    inline void setType(Type _type){type = _type;}
    
    inline const QString& getLabel() const{return label;}
    inline void setLabel(const QString& _label){label = _label;}
    
    inline const QString& getUUID() const{return uuid;}
    inline void setUUID(const QString& _uuid){uuid = _uuid;}
    
    inline Object& operator =(const Object& ref) {
        type = ref.type;
        label = ref.label;
        uuid = ref.uuid;
        return *this;
    }
    
    inline bool operator ==(const Object& ref) const {
        return type == ref.type && uuid == ref.uuid && label == ref.label;
    }
    inline bool operator !=(const Object& ref) const {
        return type != ref.type || uuid != ref.uuid || label != ref.label;
    }
private:
    Type type;
    QString label;
    QString uuid;
};

class Circuit::Element:public Object {
    Circuitling::ElementType elementType;
    qreal x;
    qreal y;
public:
    explicit Element(Circuitling::ElementType _type);
    explicit Element(const QString& _label, Circuitling::ElementType _type);
    explicit Element(qreal _x, qreal _y, Circuitling::ElementType _type);
    Element(const Element&);
    ~Element();

    Element& operator =(const Element&);

    bool operator ==(const Element&) const;
    bool operator !=(const Element&) const;

    inline Circuitling::ElementType getElementType() const {
        return elementType;
    }

    inline void setElementType(Circuitling::ElementType _type) {
        elementType = _type;
    }

    inline qreal getX() const {
        return x;
    }

    inline qreal getY() const {
        return y;
    }

    inline void locate(qreal _x, qreal _y) {
        x = _x;
        y = _y;
    }
};

class Circuit::Connection:public Object{
    class Element* elementA;
    class Element* elementB;
public:
    explicit Connection(class Element* a, class Element* b);
    Connection(const Connection&);
    ~Connection();

    Connection& operator =(const Connection&);

    bool operator==(const Connection&) const;
    bool operator!=(const Connection&) const;
    
    inline class Element* getConnectedElement(class Element* element) const{
        if(element == elementA || element == elementB)
            return element == elementA ? elementB : elementA;
        return 0;
    }

    inline class Element* getElementA() const {
        return elementA;
    }

    inline void setElementA(class Element* _a) {
        elementA = _a;
    }

    inline class Element* getElementB() const {
        return elementB;
    }

    inline void setElementB(class Element* _b) {
        elementB = _b;
    }
    
    inline bool isValid() const{
        return elementA && elementB;
    }

};

#endif

