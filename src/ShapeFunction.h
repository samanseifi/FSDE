/*
 * ShapeFunction.h
 *
 *  Created on: Aug 23, 2018
 *      Author: saman
 */

#ifndef SHAPEFUNCTION_H_
#define SHAPEFUNCTION_H_

#include "Element.h"
#include <eigen3/Eigen/Dense>

namespace FSDE {

class ShapeFunction {
public:

	ShapeFunction();

	ShapeFunction(double ,double);

	virtual ~ShapeFunction();

	Eigen::VectorXd NA_vec();



private:

		double _N1;
		double _N2;
		double _N3;
		double _N4;

		double _DN11;
		double _DN21;
		double _DN31;
		double _DN41;

		double _DN12;
		double _DN22;
		double _DN32;
		double _DN42;



};

} /* namespace FSDE */

#endif /* SHAPEFUNCTION_H_ */
