//============================================================================
// Name        : ContactTracer.cpp
// Author      : Andrea Roccaccino, Federico Masssaro
// Version     : Alpha 0.1
// Description : Helps determining chance of infection in a node network
//============================================================================

#include <iostream>
using namespace std;

#include <string>
#include <fstream>

#include "Graph/graph.h"
#include "Graph/Rules/rule.h"

#include "Graph/Rules/Chance/collection_chance_functions.h"

Graph g;
void writeToFile() {
	ofstream of;
	of.open("out.txt");
	of << g;
	of.close();
}

void readFile() {
	ifstream in;
	in.open("out.txt");
	in >> g;
	in.close();
}

void print_chance(string node){
	cout << "Infection chance of " << node << " is " << (g.get_node_infection_chance(node)*100) << "%\n";
}

int main() {

	//readFile();
	g.add_node(Node::NodeFactory(string("nodo0")).set_type(0).getNode());
	g.add_node(Node::NodeFactory(string("nodo1")).set_type(1).getNode());
	g.add_node(Node::NodeFactory(string("nodo2")).set_type(2).getNode());
	g.add_node(Node::NodeFactory(string("nodo3")).set_type(0).getNode());
	g.add_node(Node::NodeFactory(string("nodo4")).set_type(1).getNode());
	g.add_node(Node::NodeFactory(string("nodo5")).set_type(2).getNode());
/*	g.add_node(Node::NodeFactory(string("nodo6")).set_type(0).getNode());
	g.add_node(Node::NodeFactory(string("nodo7")).set_type(1).getNode());
	g.add_node(Node::NodeFactory(string("nodo8")).set_type(2).getNode());
	g.add_node(Node::NodeFactory(string("nodo9")).set_type(0).getNode());
	g.add_node(Node::NodeFactory(string("nodo10")).set_type(1).getNode());
	g.add_node(Node::NodeFactory(string("nodo11")).set_type(2).getNode());
	g.add_node(Node::NodeFactory(string("nodo12")).set_type(2).getNode());
	g.add_node(Node::NodeFactory(string("nodo13")).set_type(0).getNode());
	g.add_node(Node::NodeFactory(string("nodo14")).set_type(1).getNode());
	g.add_node(Node::NodeFactory(string("nodo15")).set_type(2).getNode());
	g.add_node(Node::NodeFactory(string("nodo16")).set_type(0).getNode());
	g.add_node(Node::NodeFactory(string("nodo17")).set_type(1).getNode());
	g.add_node(Node::NodeFactory(string("nodo18")).set_type(2).getNode());*/

	g.add_contact(string("nodo0"), string("nodo1"), 0.1, 10, string("2021-02-02 23:59"));
	g.add_contact(string("nodo1"), string("nodo2"), 0.5, 3, string("2021-02-02 23:59"));
	g.add_contact(string("nodo2"), string("nodo3"), 1, 1, string("2021-02-02 23:59"));
	g.add_contact(string("nodo3"), string("nodo4"), 0.1, 3, string("2021-02-02 23:59"));
	//g.add_contact(string("nodo1"), string("nodo2"), 1, 1.2, string("2021-02-02 23:59"));

	writeToFile();



	g.mark_infected(string("nodo0"), 1);
	//g.mark_infected(string("nodo4"), 1);

	ComplexRule *sr = new ComplexRule();
	g.apply_rule(((Rule*)sr));

	//g.print_node(string("nodo7"), cout);

	//cout << Normal::chance_between(1, 2, 0, 2);

	cout << g << endl;

	print_chance("nodo0");
	print_chance("nodo1");
	print_chance("nodo2");
	print_chance("nodo3");
	print_chance("nodo4");

	//cout << g.is_contact(string("nodoB"), string("nodo1")) << endl;

	return 0;
}
