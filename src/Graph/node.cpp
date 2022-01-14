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
		if ((*it)->get_other_node(n) == this)
			return *it;
		it++;
	}
	return nullptr;
}

void Node::add_contact(Contact *c) {
	if (!find_link(c->get_other_node(this)))
		contacts.push_back(c);
}

void Node::delete_all_contacts_both() {
	list<Contact*>::iterator it = contacts.begin();
	while ((it = contacts.begin()) != contacts.end()) {
		delete_contact_both(*it);
		it++;
	}
	contacts.clear();
}

void Node::get_next_tempid(Contact::TempID **tid) {
	if (*tid == nullptr) {
		inside_iterator = contacts.begin();
		if (inside_iterator == contacts.end())
			*tid = nullptr;
		else
			*tid = (**inside_iterator).get_temp_id();
		return;
	}

	(**inside_iterator).sync_temp_id();
	(**inside_iterator).second->add_contact(*inside_iterator);
	inside_iterator++;

	if (inside_iterator == contacts.end()) {
		*tid = nullptr;
		return;
	} else {
		*tid = (**inside_iterator).get_temp_id();
	}
}

void Node::set_infection_chance(float infection_chance) {
	this->infection_chance = infection_chance > 1.0f ? 1 :
								infection_chance < 0.0f ? 0 : infection_chance;
}

void Node::set_infected(bool infected) {
	infection_chance = infected ? 1 : 0;
}

void Node::add_or_update(Node *n, float distance, float exposure,
		std::string date) {
	Contact *c = find_link(n);
	if (!c) {
		c = new Contact(distance, exposure, date, this, n);
		add_contact(c);
		n->add_contact(c);
	} else {
		c->update(distance, exposure, date);
	}
}

void Node::delete_contact_both(Contact *c) {
	if (!c)
		return; // can't delete null pointer
	this->delete_contact(c);
	c->get_other_node(this)->delete_contact(c);
	c = nullptr;
}

void Node::delete_contact(Contact *c) {
	this->contacts.remove(c);
}

void Node::print_contact(Node *n, std::ostream &out) const {
	Contact *c = find_link(n);
	if (c) {
		out << c->get_exposure() << " minutes at " << c->get_distance()
				<< " meters on " << c->get_date() << std::endl;
	} else {
		out << "Not in contact." << std::endl;
	}
}
