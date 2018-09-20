/*
 * Element.cpp
 *
 *  Created on: Aug 18, 2018
 *      Author: saman
 */

#include "Element.h"

namespace FSDE
{

Element::Element(): _ID(), _node_vector() {

}


Element::Element(int ID, vector<Node> nodes, vector<Edge> edges){
    _ID     = ID;
    _node_vector = nodes;
    _edge_vector = edges;

}

Element::Element(int ID, vector<Node> nodes){
	_ID = ID;
	_node_vector = nodes;

}

Element::~Element(){

}


vector<Node> Element::GetNodeVector() {
    return _node_vector;
}

vector<Edge> Element::GetEdgeVector() {
  	return _edge_vector;
}

void Element::SetElemType(string elemName) {
	this->_elem_name = elemName;
}


int Element::GetID() {
	return _ID;
}

void Element::SetEdgeVector(vector<Edge> edges) {
	_edge_vector = edges;
}


const double Element::ElementVolume(void) {
	double vol;
	if (this->_elem_name == "SHELL4") {
		vol = ElementArea();
	} else if (this->_elem_name == "HEX8") {
		vol = 1.0;
	}
	return vol;
}

const double Element::ElementArea(void) {
	return 1.0;
}

} // namespace FSDE2D
