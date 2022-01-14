/*
 * graph.cpp
 *
 *  Created on: 22 dic 2021
 *      Author: Andrea
 */

#include "graph.h"

Graph::Graph() {

}

Graph::~Graph() {
	delete_all_nodes();
}

void Graph::delete_all_nodes() {
	list<Node*>::iterator it = nodes.begin();
	while ((it = nodes.begin()) != nodes.end()) {
		delete_node(*it);
		it++;
	}
	nodes.clear();
}

Node* Graph::find_node(std::string ID) const {
	list<Node*>::const_iterator it = nodes.begin();
	while (it != nodes.end()) {
		if (((*it)->get_id()) == ID)
			return *it;
		it++;
	}
	return nullptr;
}

void Graph::add_contact(std::string ID1, std::string ID2, float distance,
		float exposure, std::string date, Rule *r) {
	Node *n1 = find_node(ID1), *n2 = find_node(ID2);
	if ((n1 != nullptr) && (n2 != nullptr)) {
		n1->add_or_update(n2, distance, exposure, date);
		r->calculate_node(n1);
	} else {
		// Nodes not on the graph! Contact is not valid.
	}
}

void Graph::add_contact(std::string ID1, std::string ID2, float distance,
		float exposure, std::string date) {
	Node *n1 = find_node(ID1), *n2 = find_node(ID2);
	if ((n1 != nullptr) && (n2 != nullptr)) {
		n1->add_or_update(n2, distance, exposure, date);
	} else {
		// Nodes not on the graph! Contact is not valid.
	}
}

void Graph::add_node(Node *n) {
	if (!find_node(n->get_id()))
		nodes.push_back(n);
	else {
		// This node is NOT UNIQUE! Can't add duplicate nodes.
	}
}

bool Graph::is_contact(std::string ID1, std::string ID2) {
	Node *n1 = find_node(ID1), *n2 = find_node(ID2);
	return n1 && n2 ? (n1->is_contact(n2)) : false;
}

void Graph::print_contact(std::string ID1, std::string ID2,
		std::ostream &out) const {
	Node *n1 = find_node(ID1), *n2 = find_node(ID2);
	if (n1 && n2)
		n1->print_contact(n2, out);
	else
		out << "No contact" << endl;
}

void Graph::apply_rule(Rule *r) {
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

void Graph::printall(std::ostream &out) const {
	list<Node*>::const_iterator it = nodes.begin();
	while (it != nodes.end()) {
		cout << "Infection chance of " << (**it).get_id() << " is "
				<< ((**it).get_infection_chance() * 100) << "%\n";
		it++;
	}
}

float Graph::get_node_infection_chance(std::string ID) const {
	Node *n = find_node(ID);
	return n ? n->get_infection_chance() : 0;
}

void Graph::mark_infected(std::string ID, bool infected) {
	Node *n = find_node(ID);
	if (n) {
		n->set_infected(infected);
	}
}
void Graph::mark_infected(std::string ID, bool infected, Rule *r) {
	Node *n = find_node(ID);
	if (n) {
		n->set_infected(infected);
		r->calculate_node(n);
	}
}

void Graph::delete_contact(std::string ID1, std::string ID2) {
	Node *n2 = find_node(ID2), *n1 = find_node(ID1);
	if (n1 && n2)
		delete_contact(n1, n2);
}

void Graph::delete_node(std::string ID) {
	delete_node(find_node(ID));
}

void Graph::delete_node(Node *n) {
	if (n) {
		nodes.remove(n);
		delete n;
		n = nullptr;
	}
}
