/*
 * Nodesets.cpp
 *
 *  Created on: Aug 18, 2018
 *      Author: saman
 */

#include "Nodesets.h"

namespace FSDE
{

Nodesets::Nodesets(vector<Node> nodes, int ID) {

	_ID = ID;
	_size = nodes.size();
    _nodes = nodes;

}

Nodesets::~Nodesets() {

}

int Nodesets::GetID() {
	return _ID;
}

vector<Node> Nodesets::GetNodes() {
	return _nodes;
}

}
