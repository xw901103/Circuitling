#ifndef CIRCUIT_H
#define CIRCUIT_H

#include <QString>
#include <QMap>
#include <QDomDocument>

class Circuit{
public:
	class Element;
	class Connection;

	enum ElementType{
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

	inline void setUUID(const QString& _uuid){uuid = _uuid;}

	inline QString getTitle() const{return title;}
	inline void setTitle(const QString& _title){title = _title;}

	QDomDocument toDomDocument() const;
private:
	QMap<QString, Element> elementMap;
	QMap<QString, Connection> connectionMap;
	QString uuid;
	QString title;
};

class Circuit::Element{
	QString label;
	ElementType type;
public:
	Element();
	~Element();

	inline QString getLabel() const{return label;}
	inline void setLabel(const QString& _label){label = _label;}

	inline ElementType getType() const{return type;}
	inline void setType(ElementType _type){type = _type;}
};

class Circuit::Connection{
	Element* elementA;
	Element* elementB;
public:
	explicit Connection(Element* a, Element* b);
	~Connection();

	Element* getElementA() const{return elementA;}
	void setElementA(Element* _a){elementA = _a;}

	Element* getElementB() const{return elementB;}
	void setElementB(Element* _b){elementB = _b;}

};

#endif

