#ifndef CIRCUIT_H
#define CIRCUIT_H

#include <QString>

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

