#include "circuit.h"

Circuit::Circuit(){
}

Circuit::~Circuit(){
}

Circuit::Element::Element(){
}

Circuit::Element::~Element(){
}

Circuit::Connection::Connection(Element* a, Element* b):elementA(a), elementB(b){
}

Circuit::Connection::~Connection(){}
