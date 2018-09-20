/*
 * factorial.cpp
 *
 *  Created on: Aug 18, 2018
 *      Author: saman
 */
int factorial(int n) {
	int result = 1;
	for (int i = 1; i <= n; i++) {
		result *= i;
	}
	return result;

}
