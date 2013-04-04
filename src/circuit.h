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
#ifndef CIRCUIT_H
#define CIRCUIT_H

#include <QString>
#include <QMap>
#include <QDomDocument>

class Circuit {
public:
    class Element;
    class Connection;

    enum ElementType {
        Node,
        Resistor,
        VolatageSource,
        CurrentSource,
        Capacitor,
        Indicator,
        CustomizedElement
    };

    Circuit();
    ~Circuit();

    Element* getElement(const QString& uuid);
    QString addElement(const Element&);
    void delElement(const QString& uuid);

    Connection* getConnection(const QString& uuid);
    QString addConnection(const Connection&);
    void delConnection(const QString& uuid);

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

    QDomDocument toDomDocument() const;
private:
    QMap<QString, Element> elementMap;
    QMap<QString, Connection> connectionMap;
    QString uuid;
    QString title;
    qreal x;
    qreal y;
};

class Circuit::Element {
    QString label;
    ElementType type;
public:
    Element();
    ~Element();

    inline QString getLabel() const {
        return label;
    }

    inline void setLabel(const QString& _label) {
        label = _label;
    }

    inline ElementType getType() const {
        return type;
    }

    inline void setType(ElementType _type) {
        type = _type;
    }
};

class Circuit::Connection {
    Element* elementA;
    Element* elementB;
public:
    explicit Connection(Element* a, Element* b);
    ~Connection();

    Element* getElementA() const {
        return elementA;
    }

    void setElementA(Element* _a) {
        elementA = _a;
    }

    Element* getElementB() const {
        return elementB;
    }

    void setElementB(Element* _b) {
        elementB = _b;
    }

};

#endif

