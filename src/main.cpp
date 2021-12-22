//============================================================================
// Name        : ContactTracer.cpp
// Author      : Andrea Roccaccino, Federico Masssaro
// Version     : Alpha 0.1
// Description : Helps determining chance of infection in a node network
//============================================================================

#include <iostream>
using namespace std;

#include <string>

#include "Graph/graph.h"


int main() {
	Graph g;

	g.add_node(Node::NodeFactory(string("nodo")).set_type(0).getNode());
	g.add_node(Node::NodeFactory(string("nodo1")).set_type(1).getNode());
	g.add_node(Node::NodeFactory(string("nodo2")).set_type(2).getNode());

	g.add_contact(string("nodo1"), string("nodo2"), 2, 1.2, string("2021-02-02 23:59"));

	cout << "Contact? " << g.is_contact(string("nodo1"), string("nodo2")) << endl;


	return 0;
}
