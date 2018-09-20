/*
 * Element.h
 *
 *  Created on: Aug 18, 2018
 *      Author: saman
 */

#ifndef ELEMENT_H_
#define ELEMENT_H_

#include "Edge.h"

namespace FSDE
{

class Element {
public:

	Element();

	Element(int, vector<Node>, vector<Edge>);

	Element(int, vector<Node>);

	virtual ~Element();

	vector<Node> GetNodeVector();

	vector<Edge> GetEdgeVector();

	void SetEdgeVector(vector<Edge>);

	int GetID();

	void SetElemType(string);

	const double ElementVolume(void);

	const double ElementArea(void);

protected:

	string _elem_name;

private:


	int _ID;

	vector<Node> _node_vector;

	vector<Edge> _edge_vector;

//	string *strElemType;




};
} /* namespace FSDE */

#endif /* ELEMENT_H_ */
