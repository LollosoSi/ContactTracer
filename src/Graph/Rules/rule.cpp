/*
 * rule.cpp
 *
 *  Created on: 21 dic 2021
 *      Author: Andrea
 */

#include "rule.h"


Node* higher_chance_node(Contact &c){
	return ((c.first->get_infection_chance()) - (c.second->get_infection_chance())) <= 0 ? nullptr : c.first->get_infection_chance() > c.second->get_infection_chance() ? c.first : c.second;
}

/*
Node* other_node(Contact &c, Node *n){
	return n == c.first ? c.second : c.first;
}*/

void SimpleRule::calc(Contact &c){
	Node *h = higher_chance_node(c);
	if(h){
		c.get_other_node(h)->set_infection_chance(h->get_infection_chance()-20);
		//other_node(c,h)->propagate_rule(((Rule)*this));
	}
}
