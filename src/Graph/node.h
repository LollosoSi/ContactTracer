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
	inline virtual unsigned int get_type() const {
		return type;
	}

	/** @brief Infection chance
	 * 	@returns Infection chance of node. Range [0.0 to 1.0]
	 * 	@author Andrea
	 */
	inline float get_infection_chance() const {
		return infection_chance;
	}

	/** @brief sets infection chance
	 * 	@author Andrea
	 */
	void set_infection_chance(float infection_chance);

	/**	@brief Mark node as infected or clean
	 * 	@desc Marks node as infected or clean. Sets infection chance to either 0 or 1
	 * 	@author Andrea
	 */
	void set_infected(bool infected);

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
	inline std::string get_id() const {
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
	inline void delete_contact_with_both(Node *n) {
		delete_contact_both(find_link(n));
	}

	/** Removes every contact from list, from other nodes and frees memory
	 *
	 */
	void delete_all_contacts_both();

	void add_or_update(Node *n, float distance, float exposure,
			std::string date);

	/**
	 * @returns true if link with such node exists
	 */
	inline bool is_contact(Node *n) const {
		return find_link(n) != nullptr;
	}

	// TODO: complete implementation & deserialization
	friend std::ostream& operator<<(std::ostream &out, const Node &n) {
		out << n.id << divider_node << n.type << divider_node
				<< n.infection_chance;
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

		// We can't extract data from an empty string. As such, we'll leave an empty node that will be deleted later
		if (std::strlen(line) == 0) {
			n.id = string("");

			return in;
		}

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

			char *d1 = std::strtok(line + cursor, divider_node);
			cursor += 1 + std::strlen(d1);

			data = std::strtok(NULL, divider_node);
			cursor += 1 + std::strlen(data);

			c->add_temp_id(std::string(d1), std::string(data));
			n.add_contact(c);
		}

		return in;
	}

	list<Contact*>::iterator inside_iterator;
	void get_next_tempid(Contact::TempID **tid);

	/** Ensures no changes can be done over contacts
	 *	NOTE: Might need a different implementation
	 */
	list<Contact*>::const_iterator get_contact_constant_iterator_begin() const {
		return contacts.begin();
	}
	list<Contact*>::const_iterator get_contact_constant_iterator_end() const {
		return contacts.end();
	}

	/* Unused code. Replaced with get_contact_constant_iterator
	 list<Contact*>::iterator inside_iterator_contacts;
	 void get_next_contact(Contact **c) {
	 if (*c == nullptr) {
	 inside_iterator_contacts = contacts.begin();
	 if (inside_iterator_contacts == contacts.end())
	 *c = nullptr;
	 else
	 *c = (*inside_iterator_contacts);
	 return;
	 }


	 inside_iterator_contacts++;

	 if (inside_iterator_contacts == contacts.end()) {
	 *c = nullptr;
	 return;
	 } else {
	 *c = (*inside_iterator_contacts);
	 }
	 }
	 */

	/**  Constructor of Node object
	 * 	@brief Allows for faster building of a Node object and must be used to ensure compatibility
	 */
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
		inline NodeFactory set_type(unsigned int type) {
			this->type = type;
			return *this;
		}
		/** Sets id of future node
		 *	@param id unique string
		 *	@returns self
		 */
		inline NodeFactory set_id(std::string id) {
			this->id = id;
			return *this;
		}

		/** Sets infection chance of future node
		 *	@returns self
		 */
		inline NodeFactory set_infection_chance(float chance) {
			this->infection_chance = chance;
			return *this;
		}

		/**
		 * @returns new node instance with the specified parameters
		 */
		inline Node* getNode() {
			Node *n = new Node(id, type);
			n->set_infection_chance(infection_chance);
			return n;
		}

	private:
		std::string id = "";
		unsigned int type = 0;
		float infection_chance = 0;
	};

	/** Pretty prints contact data to ostream */
	void print_contact(Node *n, std::ostream &out) const;

	/**
	 * @brief Creates and adds a contact to pointer contact list, for both nodes
	 * @deprecated Contact creation is handled in the Graph object
	 * @param *n Target node to be linked
	 * @param exposure Time of exposure
	 * @param distance Distance within contact took place
	 * @param date Date+Time of contact
	 * @author Andrea
	 */
	void add_contact(Node *n, float exposure, float distance, string date) {
		//Contact *c = new Contact(distance, exposure, date, this, n); add_contact(c); n->add_contact(c);
		std::cerr << "Use of deprecated function.\nPlease use the Graph object in order to create contacts.\n";
	}

protected:

	/** Returns the contact pointer or nullptr if not found
	 *	@param n second node to be found
	 */
	Contact* find_link(Node *n) const;

	/** @brief Empty constructor of class
	 *  NOTE: This object must be instanced from a NodeFactory object
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
	void delete_contact(Contact *c);

	/** Removes contact from list
	 * 	NOTE: Enclosed call
	 * 	NOTE: Protected function due to Encapsulation practices
	 *	@param c Contact to be removed
	 */
	void delete_contact_both(Contact *c);

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
	virtual inline void set_type(unsigned int type) {
		this->type = type;
	}

private:

	/** Contact list */
	list<Contact*> contacts;
};

