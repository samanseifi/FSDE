/*
 * Node.cpp
 *
 *  Created on: Aug 18, 2018
 *      Author: saman
 */

#include "Node.h"

namespace FSDE
{
Node::Node() : _ID(), _xc(), _yc(), _zc() {

}

Node::Node(int ID, double x_coord, double y_coord): _zc() {
	_ID = ID;

	_xc = x_coord;
	_yc = y_coord;
}

Node::Node(int ID, double x_coord, double y_coord, double z_coord) {
	_ID = ID;

	_xc = x_coord;
	_yc = y_coord;
	_zc = z_coord;
}

Node::~Node() {

}

int Node::GetID() const {
	return _ID;
}

vector<double> Node::GetCoordinates() {

	vector<double> coordsVec(2, 0); // initialize the vector with zeros

	coordsVec[0] = _xc;
	coordsVec[1] = _yc;
	if (_zc) {
		coordsVec.push_back(_zc);
	}

	return coordsVec;
}

void Node::UpdateCoordinates(double disp_x, double disp_y) {

	this->_xc += disp_x;
	this->_yc += disp_y;

}

void Node::UpdateCoordinates(double disp_x, double disp_y, double disp_z) {
	this->_xc += disp_x;
	this->_yc += disp_y;
	this->_zc += disp_z;
}
//
//void Node::connected(int ndID){
//	ndID = 0;
//}


//bool Node::isConnectedWith(Node nd1) {
//
//}

}
