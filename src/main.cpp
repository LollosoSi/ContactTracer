//============================================================================
// Name        : ContactTracer.cpp
// Author      : Andrea Roccaccino, Federico Masssaro
// Version     : Alpha 0.1
// Description : Helps determining chance of infection in a node network
//============================================================================

#include <iostream>
using namespace std;

#include "consolecommands.h"

int main() {


	sendcommand();

	/*
	//readFile();

	g.add_node(Node::NodeFactory(string("1")).set_type(0).getNode());
	g.add_node(Node::NodeFactory(string("2")).set_type(0).getNode());
	g.add_node(Node::NodeFactory(string("3")).set_type(0).getNode());
	g.add_node(Node::NodeFactory(string("4")).set_type(0).getNode());

	g.add_contact(string("1"), string("3"), 0.1, 5, string("2021-02-02 23:59"),
			rule);

	writeToFile();

	g.mark_infected(string("1"), 1, rule);
	//g.mark_infected(string("nodo4"), 1);

	// We don't need to propagate rule since it is handled when marking and when setting contact
	//g.apply_rule(((Rule*)sr));

	//g.print_node(string("nodo7"), cout);

	cout << g << endl;

	print_chance("2");

	//cout << g.is_contact(string("nodoB"), string("nodo1")) << endl;*/

	return 0;
}
