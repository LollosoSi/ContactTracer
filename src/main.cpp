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

Graph g;
void writeToFile(){
	ofstream of;
	of.open("out.txt");
	of << g;
	of.close();
}

void readFile(){
	ifstream in;
	in.open("out.txt");
	in >> g;
	in.close();
}

int main() {

/*
	g.add_node(Node::NodeFactory(string("nodo0")).set_type(0).getNode());
	g.add_node(Node::NodeFactory(string("nodo1")).set_type(1).set_infection_chance(0.5).getNode());
	g.add_node(Node::NodeFactory(string("nodo2")).set_infection_chance(0.3).set_type(2).getNode());

	g.add_contact(string("nodo1"), string("nodo2"), 2, 1.2, string("2021-02-02 23:59"));
	writeToFile();
	*/
	readFile();
	cout << g << endl;

	g.delete_all_nodes();
	cout << g;

	return 0;
}
