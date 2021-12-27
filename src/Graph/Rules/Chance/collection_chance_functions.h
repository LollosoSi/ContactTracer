/*
 * collection_chance_functions.h
 *
 *  Created on: 24 dic 2021
 *      Author: arocc
 */

#pragma once

#include <cmath>



class Normal{
public:
	/** Calculates chance at X using Gaussian function
	 * @param x indipendent variable
	 * @param m Average of gauss (middle point)
	 * @param s2 Square Sigma
	 */
	static float instant_chance(float x, float m, float s2) {
		return pow(M_E,(-pow(x-m,2)/(2*s2)))/(sqrt(2*M_PI*s2));
	}

	static float chance_between(float x, float x1, float m, float s2){
		float sum = 0;
		float step = 0.1;
		for (float i = min(x,x1); i < max(x,x1); i+=step){
			sum += instant_chance(i,m,s2)*step;
		}
		return sum;
	}
};

class Exponential{
public:
	/** Calculates chance at X using Gaussian function
	 * @param x indipendent variable
	 * @param lambda lambda
	 */
	static float instant_chance(float x, float lambda) {
		return lambda*pow(M_E,-(lambda*x));
	}

	static float chance_between(float x, float x1, float lambda){
		float sum = 0;
		float step = 0.1;
		for (float i = min(x,x1); i < max(x,x1); i+=step){
			sum += instant_chance(i,lambda)*step;
		}
		return sum;
	}

};
