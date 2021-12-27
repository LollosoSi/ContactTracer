/*
 * rule.h
 *
 *  Created on: 21 dic 2021
 *      Author: Andrea
 */

#pragma once

#include "../node.h"
#include "../Arcs/contact.h"
#include "Chance/collection_chance_functions.h"

#include <iostream>
using namespace std;

class Rule {
public:
	Rule() {
	}
	virtual ~Rule() {
	}
	/**	Calculates and assigns actual node infection chance
	 *  Recursive
	 */
	virtual void calc(Contact &c){}
	virtual void calculate_node(Node *n) {
		std::list<Contact*>::const_iterator ci =
				n->get_contact_constant_iterator_begin();
		while (ci != n->get_contact_constant_iterator_end()) {
			calc((**ci));
			ci++;
		}
	}

};

class SimpleRule: public Rule {
public:
	SimpleRule() :
			Rule() {
	}
	virtual ~SimpleRule() {
	}
	void calc(Contact &c);
};

class ComplexRule : public Rule {
public:
	ComplexRule() : Rule() {

	}
	virtual ~ComplexRule() {};
	void calc(Contact &c);
};

class DistanceRule : public Rule{

	void calc (Contact &c);

};
