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


Rule *rule = new SimpleRule();

int main() {


	//readFile();
	char* buf = new char[10];
	for(int i = 1; i < 21; i++){
		itoa(i, buf, 10);
		g.add_node(Node::NodeFactory(string(buf)).set_type(0).getNode());
	}
	delete [] buf;

	g.add_contact(string("1"), string("5"), 0.1, 2, string("2021-02-02 23:59"), rule);
	g.add_contact(string("5"), string("9"), 0.1, 2, string("2021-02-02 23:59"), rule);
	g.add_contact(string("10"), string("9"), 0.1, 2, string("2021-02-02 23:59"), rule);
	g.add_contact(string("10"), string("11"), 0.1, 2, string("2021-02-02 23:59"), rule);
	g.add_contact(string("6"), string("11"), 0.1, 2, string("2021-02-02 23:59"), rule);
	g.add_contact(string("6"), string("12"), 0.1, 2, string("2021-02-02 23:59"), rule);
	g.add_contact(string("7"), string("12"), 0.1, 2, string("2021-02-02 23:59"), rule);
	g.add_contact(string("7"), string("4"), 0.1, 2, string("2021-02-02 23:59"), rule);
	g.add_contact(string("3"), string("4"), 0.1, 2, string("2021-02-02 23:59"), rule);
	g.add_contact(string("3"), string("2"), 0.1, 2, string("2021-02-02 23:59"), rule);

	g.add_contact(string("12"), string("17"), 0.1, 2, string("2021-02-02 23:59"), rule);
	g.add_contact(string("20"), string("17"), 0.1, 2, string("2021-02-02 23:59"), rule);
	g.add_contact(string("20"), string("19"), 0.1, 2, string("2021-02-02 23:59"), rule);
	g.add_contact(string("19"), string("16"), 0.1, 2, string("2021-02-02 23:59"), rule);
	g.add_contact(string("13"), string("20"), 0.1, 2, string("2021-02-02 23:59"), rule);
	g.add_contact(string("14"), string("20"), 0.1, 2, string("2021-02-02 23:59"), rule);
	g.add_contact(string("15"), string("18"), 0.1, 2, string("2021-02-02 23:59"), rule);
	g.add_contact(string("15"), string("9"), 0.1, 2, string("2021-02-02 23:59"), rule);
	g.add_contact(string("16"), string("18"), 0.1, 2, string("2021-02-02 23:59"), rule);


	g.add_contact(string("14"), string("8"), 0.1, 2, string("2021-02-02 23:59"), rule);
	g.add_contact(string("8"), string("4"), 0.1, 2, string("2021-02-02 23:59"), rule);


	writeToFile();


	g.mark_infected(string("9"), 1, rule);
	//g.mark_infected(string("nodo4"), 1);

	// We don't need to propagate rule since it is handled when marking and when setting contact
	//g.apply_rule(((Rule*)sr));

	//g.print_node(string("nodo7"), cout);

	cout << g << endl;

	char* buff = new char[10];
		for(int i = 1; i < 21; i++){
			itoa(i, buff, 10);
			print_chance(string(buff));
		}
		delete [] buff;


	//cout << g.is_contact(string("nodoB"), string("nodo1")) << endl;

	return 0;
}
