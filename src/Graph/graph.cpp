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
	while ((it=nodes.begin()) != nodes.end()) {
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
		float exposure, std::string date) {
	Node *n1 = find_node(ID1), *n2 = find_node(ID2);
	if (n1 && n2) {
		n1->add_or_update(n2, distance, exposure, date);
	} else {
		// Nodes not on the graph! Contact is not valid.
	}
}
