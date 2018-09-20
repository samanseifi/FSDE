/*
 * Edge.h
 *
 *  Created on: Aug 27, 2018
 *      Author: saman
 */

#ifndef EDGE_H_
#define EDGE_H_

#include "Node.h"

namespace FSDE
{

class Edge {
public:

    Edge();

    Edge(pair<Node, Node>);

    virtual ~Edge();

    Node GetFirstNode() const;
    Node GetSecondNode() const;

    bool isTheSameEdge(const Edge&);

private:

    int _ID;

    vector<Node> _nodes;

    Node _node1;
    Node _node2;


};


} /* namespace FSDE */


#endif /* EDGE_H_ */
