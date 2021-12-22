/*
 * rule.h
 *
 *  Created on: 21 dic 2021
 *      Author: Andrea
 */

#pragma once

#include "../node.h"
#include "../Arcs/contact.h"

#include <iostream>
using namespace std;

class Rule{
public:
	Rule();
	virtual ~Rule(){}
	virtual void calc(Contact &c){}
};


class SimpleRule : public Rule{
	void calc(Contact &c);
};
