/*
 * graph.h
 *
 *  Created on: 22 dic 2021
 *      Author: Andrea
 */

#pragma once

#include "node.h"
#include "Arcs/contact.h"

#include <list>
#include <string>

/** Handles the whole Graph. Interface to other developers */
class Graph {
public:
	/** Costruttore */
	Graph();

	/** Distruttore */
	virtual ~Graph();

	/** Deletes one node from graph
	 *	@param ID unique identifier of node
	 */
	void delete_node(std::string ID) {
		delete_node(find_node(ID));
	}

	/**
	 *  @brief Correctly frees memories of all nodes and insides.
	 */
	void delete_all_nodes();

	/** Creates a new Contact object and inserts in the
	 * NODE: Insertion occurs only if a valid Contact object can be created
	 */
	void add_contact(std::string ID1, std::string ID2, float distance,
			float exposure, std::string date);

	/**
	 * @brief Deletes a contact from both nodes and memory
	 */
	void delete_contact(std::string ID1, std::string ID2) {
		Node *n2 = find_node(ID2), *n1 = find_node(ID1);
		if (n1 && n2)
			delete_contact(n1, n2);
	}

	/** Marks a node as infected/clear (sets chance to 1 or 0)
	 *
	 */
	void mark_infected(std::string ID, bool infected) {
		find_node(ID)->set_infected(infected);
	}

	/** Adds a new node to graph
	 *	NOTE: Node must be valid
	 *	Simple enclosed call
	 */
	void add_node(Node *n) {
		if (!find_node(n->get_id()))
			nodes.push_back(n);
		else {
			// This node is NOT UNIQUE! Can't add duplicate nodes.
		}
	}

	bool is_contact(std::string ID1, std::string ID2) {
		Node *n1 = find_node(ID1), *n2 = find_node(ID2);
		return n1 && n2 ? (n1->is_contact(n2)) : false;
	}

	friend std::ostream& operator<<(std::ostream &out, const Graph &g) {
		list<Node*>::const_iterator it = g.nodes.begin();
		while (it != g.nodes.end()) {
			out << **it << std::endl;
			it++;
		}
		return out;
	}

	// TODO: Complete deserialization
	friend std::istream& operator>>(std::istream &in, Graph &g) {
		std::string data = "";
		while (!in.eof()) {

		}

		return in;
	}

protected:

	/** Deletes one node from graph
	 *	Simple enclosed call and node pointer deletion
	 */
	void delete_node(Node *n) {
		if (n) {
			nodes.remove(n);
			delete n;
		}
	}

	/** Adds a new Contact to its nodes
	 * 	NOTE: Contact must be valid prior insertion
	 * 	NOTE: Function is protected in order to ensure Contact object validity
	 *	@param c Contact pointer to be added inside each node's list
	 */
	void add_contact(Contact *c) {
		(c->get_node(0))->add_contact(c);
		(c->get_node(1))->add_contact(c);
	}

	/**
	 * @brief Deletes a contact from both nodes and memory
	 * @param c Contact object to be deleted
	 */
	void delete_contact(Contact *c) {
		c->get_node(0)->delete_contact_with_both(c->get_node(1));
	}
	/**
	 * @brief Deletes a contact from both nodes and memory
	 * @param n1, n2 Nodes to be unlinked
	 */
	void delete_contact(Node *n1, Node *n2) {
		n1->delete_contact_with_both(n2);
	}

	/**
	 * @returns Node pointer found by ID
	 */
	Node* find_node(std::string ID) const;

private:
	/** List of nodes composing graph */
	list<Node*> nodes;
};
