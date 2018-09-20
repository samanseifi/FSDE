/*
 * ShapeFunction.cpp
 *
 *  Created on: Aug 23, 2018
 *      Author: saman
 */

#include <ShapeFunction.h>

namespace FSDE {

ShapeFunction::ShapeFunction() {
	// TODO Auto-generated constructor stub
	_N1 = _N2 = _N3 = _N4 = 0.0;

	_DN11 = _DN21 = _DN31 = _DN41 = 0.0;
	_DN12 = _DN22 = _DN32 = _DN42 = 0.0;

}

// For quad element for now
ShapeFunction::ShapeFunction(double r, double s) {

	_N1 = 0.25 * (1.0 - r) * (1.0 - s);
	_N2 = 0.25 * (1.0 + r) * (1.0 - s);
    _N3 = 0.25 * (1.0 + r) * (1.0 + s);
	_N4 = 0.25 * (1.0 - r) * (1.0 + s);

	_DN11 = -0.25*(1.0 - s);
	_DN21 =  0.25*(1.0 - s);
	_DN31 =  0.25*(1.0 + s);
	_DN41 = -0.25*(1.0 + s);

	_DN12 = -0.25*(1.0 - r);
	_DN22 = -0.25*(1.0 + r);
	_DN32 =  0.25*(1.0 + r);
	_DN42 =  0.25*(1.0 - r);


}

ShapeFunction::~ShapeFunction() {
	// TODO Auto-generated destructor stub
}

Eigen::VectorXd ShapeFunction::NA_vec(){
	Eigen::VectorXd vec;
	vec(1) = _N1;
	vec(2) = _N2;
	vec(3) = _N3;
	vec(4) = _N4;

	return vec;
}


} /* namespace FSDE */
