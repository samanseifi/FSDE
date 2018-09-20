/*
 * Node.h
 *
 *  Created on: Aug 18, 2018
 *      Author: saman
 */

#ifndef NODE_H_
#define NODE_H_

#include <iostream>
#include <vector>
#include <cassert>
#include <eigen3/Eigen/Dense>


using namespace std;

namespace FSDE
{

class Node {
public:
	Node();

	Node(int, double, double);

	Node(int, double, double, double);

	virtual ~Node();

	int GetID() const;

	vector<double> GetCoordinates();

	void UpdateCoordinates(double, double);

	void UpdateCoordinates(double, double, double);


private:

	int _ID;

	double _xc;
	double _yc;
	double _zc;

};

} /* namespace FSDE */

#endif /* NODE_H_ */
