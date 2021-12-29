/*
 * rule.cpp
 *
 *  Created on: 21 dic 2021
 *      Author: Andrea
 */

#include "rule.h"

/**
 *  @returns in contact higher infection chance node's pointer
 *  @param c Contact object where to search for higher chance node
 */
Node* higher_chance_node(Contact &c) {
	return (c.first->get_infection_chance() == c.second->get_infection_chance()) ? nullptr :
			c.first->get_infection_chance() > c.second->get_infection_chance() ?
					c.first : c.second;
}

/*
 Node* other_node(Contact &c, Node *n){
 return n == c.first ? c.second : c.first;
 }*/

void SimpleRule::calc(Contact &c) {
	Node *h = higher_chance_node(c);
	if (h) {
		float ifc = h->get_infection_chance() - 0.2;
		if (c.get_other_node(h)->get_infection_chance() < ifc && ifc > 0.01f) {
			c.get_other_node(h)->set_infection_chance(ifc);
			//std::cout << "Setting ifc of " << c.get_other_node(h)->get_id() << " of " << ifc << std::endl;
			SimpleRule::calculate_node(c.get_other_node(h));
		}
	}
}

void ComplexRule::calc(Contact &c) {
	Node *h = higher_chance_node(c);
	if (h) {
		float ifc =  h->get_infection_chance() * Normal::chance_between(0,c.get_exposure(), 2, 2) * Exponential::chance_between(c.get_distance(), 10, 1.2);
		if (c.get_other_node(h)->get_infection_chance() < ifc && ifc > 0.01f) {
			c.get_other_node(h)->set_infection_chance(ifc);
			//std::cout << "Setting ifc of " << c.get_other_node(h)->get_id() << " of " << ifc << std::endl;
			calculate_node(c.get_other_node(h));
		}
	}
}

void DistanceRule::calc(Contact &c){
		// removing 0.01 for each node counts as distance
		Node *h = higher_chance_node(c);
		if(h){
			float ifc = h->get_infection_chance() - 0.01f;
			if(ifc > 0 && c.get_other_node(h)->get_infection_chance() < ifc){
				c.get_other_node(h)->set_infection_chance(ifc);
				calculate_node(c.get_other_node(h));
			}
		}
	}
