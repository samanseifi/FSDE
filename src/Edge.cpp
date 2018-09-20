/*
 * Edge.cpp
 *
 *  Created on: Aug 27, 2018
 *      Author: saman
 */

#include "Edge.h"

namespace FSDE
{

Edge::Edge(): _node1(), _node2(), _ID() {

}

Edge::Edge(pair<Node, Node> nodes_pair) {
// TODO: should figure out something about ID
	_ID = 0;

	_node1 = nodes_pair.first;
	_node2 = nodes_pair.second;

}

Edge::~Edge() {


}

bool Edge::isTheSameEdge(const Edge& edge){
	bool result = false;
	if (edge.GetFirstNode().GetID() == this->_node1.GetID() && edge.GetSecondNode().GetID() == this->_node2.GetID() ) {
		result = true;
	}
	if (edge.GetFirstNode().GetID() == this->_node2.GetID() && edge.GetSecondNode().GetID() == this->_node1.GetID() ) {
		result = true;
	}
	return result;

}

Node Edge::GetFirstNode() const {
	return _node1;
}

Node Edge::GetSecondNode() const {
	return _node2;
}





} /* namespace FSDE */
