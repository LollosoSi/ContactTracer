/*
 * node.h
 *
 *  Created on: 21 dic 2021
 *      Author: Andrea
 */

#pragma once

#include "Arcs/contact.h"
#include "Rules/enum.h"

#include <iostream>
#include <string>
#include <cstring>

/* STL */
#include <list>
// #include <algoritm> // Not supported by current toolchain

using namespace std;



/**
 *  @brief Represents on Graph entry
 *  @desc This is a basic node. Only contains its type, unique identifier and its own list of Contacts (links) with their attached data
 *  Don't forget to add your nodetype entry (enum defined in Graph/Rules/enum.h) when defining a new node type
 */
class Node {
public:

	/** @brief Destructor
	 *	@author Andrea
	 */
	virtual ~Node() {
		delete_all_contacts_both();
	}

	/** @brief Returns node type
	 * 	@returns Node type from enum
	 * 	@author andrea
	 */
	virtual unsigned int get_type() const {
		return type;
	}

	/** @brief Infection chance
	 * 	@returns Infection chance of node. Range [0.0 to 1.0]
	 * 	@author Andrea
	 */
	float get_infection_chance() const {
		return infection_chance;
	}

	/** @brief sets infection chance
	 * 	@author Andrea
	 */
	void set_infection_chance(float infection_chance) {
		this->infection_chance = infection_chance > 1.0f ? 1 : infection_chance < 0.0f ? 0 : infection_chance;
	}

	/**	@brief Mark node as infected or clean
	 * 	@desc Marks node as infected or clean. Sets infection chance to either 0 or 1
	 * 	@author Andrea
	 */
	void set_infected(bool infected) {
		infection_chance = infected ? 1 : 0;
	}

	/* Recursive calls for infection propagation using Rule parameter and contacts list
	 * 	NOTE: Invalid approach.
	 * 	@deprecated This method has been commented and will be removed
	 * 	@param r Rule to be applied
	 * 	@author Andrea
	 */
	/*void propagate_rule(Rule &r){
	 list<Contact*>::iterator it = contacts.begin();
	 while(it==contacts.end()){
	 r.calc(**it);
	 it++;
	 }
	 }*/

	/** Returns node ID */
	std::string get_id() const {
		return id;
	}

	/**
	 *  @brief Adds a contact to pointer contact list
	 *  @param c Contact to be added
	 *  NOTE: Contact must be valid prior insertion
	 */
	void add_contact(Contact *c);

	/** Removes contact from list by giving second node
	 *	@param n Node to be disconnected
	 */
	void delete_contact_with_both(Node *n) {
		delete_contact_both(find_link(n));
	}

	/** Removes every contact from list, from other nodes and frees memory
	 *
	 */
	void delete_all_contacts_both();

	void add_or_update(Node *n, float distance, float exposure,
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

	/**
	 * @returns true if link with such node exists
	 */
	bool is_contact(Node *n) const {
		return find_link(n);
	}

	// TODO: complete implementation & deserialization
	friend std::ostream& operator<<(std::ostream &out, const Node &n) {
		out << n.id << divider_node << n.type << divider_node << n.infection_chance;
		list<Contact*>::const_iterator it = n.contacts.begin();
		while (it != n.contacts.end()) {

			// Node is added only if the node being printed is first, in order to save memory
			if ((*it)->get_node(0) == &n) {
				out << divider_node;
				out << **it;

				out << divider_node;
				out << (**it).first->get_id();
				out << divider_node;
				out << (**it).second->get_id();
			}
			it++;
		}

		return out;
	}

	friend std::istream& operator>>(std::istream &in, Node &n) {
		char line[1500];
		char *data;
		unsigned int cursor = 0;
		in.getline(line, 1500);

		data = std::strtok(line, divider_node);
		n.id = string(data);
		cursor += 1 + std::strlen(data);

		data = std::strtok(NULL, divider_node);
		n.type = atoi(data);
		cursor += 1 + std::strlen(data);

		data = std::strtok(NULL, divider_node);
		n.infection_chance = atof(data);
		cursor += 1 + std::strlen(data);

		while ((data = std::strtok(NULL, divider_node))) {
			cursor += 1 + std::strlen(data);

			Contact *c = new Contact(data);

			char *d1 = std::strtok(line+cursor, divider_node);
			cursor += 1 + std::strlen(d1);

			data = std::strtok(NULL, divider_node);
			cursor += 1 + std::strlen(data);

			c->add_temp_id(std::string(d1), std::string(data));
			n.add_contact(c);
		}

		return in;
	}

	list<Contact*>::iterator inside_iterator;
	void get_next_tempid(Contact::TempID **tid) {
		if (*tid == nullptr) {
			inside_iterator = contacts.begin();
			if (inside_iterator == contacts.end())
				*tid = nullptr;
			else
				*tid = (**inside_iterator).get_temp_id();
			return;
		}

		(**inside_iterator).sync_temp_id();
		inside_iterator++;

		if (inside_iterator == contacts.end()) {
			*tid = nullptr;
			return;
		}
	}

	class NodeFactory {
	public:
		/**
		 *  Constructor set
		 */
		NodeFactory() :
				NodeFactory(node) {
		}
		NodeFactory(string id) :
				NodeFactory(id, node) {
		}
		NodeFactory(unsigned int type) :
				NodeFactory(std::string(""), type) {
		}
		NodeFactory(std::string id, unsigned int type) {
			set_id(id);
			set_type(type);
		}

		virtual ~NodeFactory() {
		}

		/** Sets type of future node
		 * @param type Value from enum
		 * @returns self
		 */
		NodeFactory set_type(unsigned int type) {
			this->type = type;
			return *this;
		}
		/** Sets id of future node
		 *	@param id unique string
		 *	@returns self
		 */
		NodeFactory set_id(std::string id) {
			this->id = id;
			return *this;
		}

		/** Sets infection chance of future node
		 *	@returns self
		 */
		NodeFactory set_infection_chance(float chance) {
			this->infection_chance = chance;
			return *this;
		}

		/**
		 * @returns new node instance with the specified parameters
		 */
		Node* getNode() {
			Node *n = new Node(id, type);
			n->set_infection_chance(infection_chance);
			return n;
		}
	private:
		std::string id = "";
		unsigned int type = 0;
		float infection_chance = 0;
	};

	/**
	 * @brief Creates and adds a contact to pointer contact list, for both nodes
	 * @deprecated Contact creation is handled in the Graph object
	 * @param *n Target node to be linked
	 * @param exposure Time of exposure
	 * @param distance Distance within contact took place
	 * @param date Date+Time of contact
	 * @author Andrea
	 */
//void add_contact(Node *n, float exposure, float distance, string date){Contact *c = new Contact(distance, exposure, date, this, n); add_contact(c); n->add_contact(c); };
protected:

	/** Returns the contact pointer or nullptr if not found
	 *	@param n second node to be found
	 */
	Contact* find_link(Node *n) const;

	/** @brief Empty constructor of class
	 *  @author Andrea
	 */
	Node() {

	}

	/** @brief Constructor taking id of node
	 * 	@param id Identifier of node, must be unique
	 *  @author Andrea
	 */
	Node(string id) :
			Node() {
		this->id = id;
	}

	/** @brief Constructor taking id and type of node
	 * 	@param id Identifier of node, must be unique
	 * 	@param type Enum node type
	 *  @author Andrea
	 */
	Node(string id, unsigned int type) :
			Node(id) {
		set_type(type);
	}

	/** Removes contact from list
	 * 	NOTE: Enclosed call
	 * 	NOTE: Protected function due to Encapsulation practices
	 *	@param c Contact to be removed
	 */
	void delete_contact(Contact *c) {
		this->contacts.remove(c);
	}

	/** Removes contact from list
	 * 	NOTE: Enclosed call
	 * 	NOTE: Protected function due to Encapsulation practices
	 *	@param c Contact to be removed
	 */
	void delete_contact_both(Contact *c) {
		if (!c)
			return; // can't delete null pointer
		this->delete_contact(c);
		c->get_other_node(this)->delete_contact(c);
		c=nullptr;
	}

	/** Returns contact list
	 *  NOTE: Bad practice, removed
	 */
//const list<Contact*> get_contact_list()const{return contacts;}
	/** Identifier of node */
	string id = "";

	/** Node type */
	unsigned int type = node;

	/** Chance of infection of node. Value range: [0.0 to 1.0] */
	float infection_chance = 0;

	/**	@brief Sets node type
	 * 	@desc Sets node type
	 * 	@param type Value from enum to be set
	 * 	@author Andrea
	 */
	virtual void set_type(unsigned int type) {
		this->type = type;
	}

private:
	/** Contact list */
	list<Contact*> contacts;
};

