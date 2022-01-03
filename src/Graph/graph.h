/*
 * graph.h
 *
 *  Created on: 22 dic 2021
 *      Author: Andrea
 */

#pragma once

#include "node.h"
#include "Arcs/contact.h"
#include "Rules/rule.h"

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
	void add_contact(std::string ID1, std::string ID2, float distance,
			float exposure, std::string date, Rule *r);

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
		Node *n = find_node(ID);
		if (n) {
			n->set_infected(infected);
		}
	}
	void mark_infected(std::string ID, bool infected, Rule *r) {
		Node *n = find_node(ID);
		if (n) {
			n->set_infected(infected);
			r->calculate_node(n);
		}
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

	/**
	 *  @brief check existence of Arc
	 *  @returns True if a contact object referencing the two nodes is found
	 *  @param ID1 Node 1 id
	 *  @param ID2 Node 2 id
	 */
	bool is_contact(std::string ID1, std::string ID2) {
		Node *n1 = find_node(ID1), *n2 = find_node(ID2);
		return n1 && n2 ? (n1->is_contact(n2)) : false;
	}

	/** Pretty prints contact information if available
	 *
	 */
	void print_contact(std::string ID1, std::string ID2, std::ostream &out){
		Node *n1 = find_node(ID1), *n2 = find_node(ID2);
		if(n1 && n2)
			n1->print_contact(n2, out);
		else
			out << "No contact" << endl;
	}

	/** Checks if node exists inside graph
	 *
	 */
	bool node_exists(std::string ID){return find_node(ID) != nullptr;}

	/**
	 *  @brief Serialization to ostream object Format: {Node}+{Contact:1}+{FirstNodeContact:1}+{SecondNodeContact:1}+{Contact:2}+{FirstNodeContact:2}+{SecondNodeContact:2}
	 */
	friend std::ostream& operator<<(std::ostream &out, const Graph &g) {
		list<Node*>::const_iterator it = g.nodes.begin();
		while (it != g.nodes.end()) {
			out << **it;
			it++;
			if (it != g.nodes.end())
				out << std::endl;
		}
		return out;
	}

	void print_node(std::string ID, std::ostream &out) {
		out << *find_node(ID);
	}

	/**
	 * @brief Deserialization from istream object <br> Format: {Node}+{Contact:1}+{FirstNodeContact:1}+{SecondNodeContact:1}+{Contact:2}+{FirstNodeContact:2}+{SecondNodeContact:2}
	 */
	friend std::istream& operator>>(std::istream &in, Graph &g) {
		g.delete_all_nodes();

		while (!in.eof()) {
			Node *n = Node::NodeFactory().getNode();
			in >> *n;
			if(n->get_id() != string("")) g.add_node(n);
			else delete n;
		}

		list<Node*>::iterator it = g.nodes.begin();
		Contact::TempID *tid = nullptr;
		while (it != g.nodes.end()) {
			(**it).get_next_tempid(&tid);
			while (tid != nullptr) {
				(*(*tid).get_node_pointer(0)) = g.find_node(
						std::string((*tid).get_id(0)));
				(*(*tid).get_node_pointer(1)) = g.find_node(
						std::string((*tid).get_id(1)));
				(**it).get_next_tempid(&tid);
			}
			it++;
		}

		return in;
	}

	/** Propagates a Rule object to all Nodes
	 * 	@brief applies rule for each contact found in node and calculates infection chance
	 * 	@param r Rule to be applied
	 * 	NOTE: Rule is a pure virtual, as such must be extended
	 */
	void apply_rule(Rule *r) {
		// The rule must be applied beginning from the nodes which have chance equal to 1
		list<Node*>::iterator it = nodes.begin();
		while (it != nodes.end()) {
			// Is this the node we want to start a chain?
			if ((**it).get_infection_chance() == 1) {
				r->calculate_node(*it);
			}
			it++;
		}
	}

	/**
	 *  @returns selected node infection chance
	 */
	float get_node_infection_chance(std::string ID) {
		Node *n = find_node(ID);
		return n ? n->get_infection_chance() : 0;
	}


	/** Pretty prints chance of all nodes to ostream */
	void printall(std::ostream &out) {
		list<Node*>::iterator it = nodes.begin();
		while (it != nodes.end()) {
			cout << "Infection chance of " << (**it).get_id() << " is "
					<< ((**it).get_infection_chance() * 100) << "%\n";
			it++;
		}
	}


protected:

	/** Deletes one node from graph
	 *	Simple enclosed call and node pointer deletion
	 */
	void delete_node(Node *n) {
		if (n) {
			nodes.remove(n);
			delete n;
			n = nullptr;
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
