/*
 * node.cpp
 *
 *  Created on: 21 dic 2021
 *      Author: Andrea
 */

#include "node.h"

/**
 * @brief Substitute for std::find
 * @author Andrea
 */
bool member(list<Contact*> cc, Contact *c) {
	list<Contact*>::iterator it = cc.begin();
	while (it != cc.end()) {
		if (c == (*it))
			return true;
		it++;
	}
	return false;
}

Contact* Node::find_link(Node *n) const {
	list<Contact*>::const_iterator it = this->contacts.begin();
	while (it != this->contacts.end()) {
		if ((*it)->get_other_node(n) == n)
			return *it;
		it++;
	}
	return nullptr;
}

void Node::add_contact(Contact *c) {
	if (!member(contacts, c))
		contacts.push_back(c);
}

void Node::delete_all_contacts_both(){
	list<Contact*>::iterator it = contacts.begin();
	while (it != contacts.end()) {
		delete_contact_both(*it);
		it++;
	}
	contacts.clear();
}
