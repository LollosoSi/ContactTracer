/*
 * consolecommands.h
 *
 *  Created on: 2 gen 2022
 *      Author: arocc
 */

#pragma once

#include <iostream>
#include <string>
#include <cstring>
#include <fstream>

#include "Graph/graph.h"
#include "Graph/Rules/rule.h"

Graph g;

Rule *rules[] = { new SimpleRule(), new ComplexRule(), new DistanceRule(),
		new ResetRule() };
Rule *rule = rules[1];

struct Bundle {
	string *data = nullptr;
	unsigned int size = 0;

	string& operator[](int p) {
		return data[p];
	}
};

void print_chance(string node) {
	cout << "Infection chance of " << node << " is "
			<< (g.get_node_infection_chance(node) * 100) << "%\n";
}

/** type checking */
bool is_int(std::string str, int &val) {
	try {
		val = std::stoi(str); //don't call c_str()
		return true;
	} catch (std::exception const &e) {
		return false;
	}
}

bool is_double(std::string str, double &val) {
	try {
		val = std::stod(str); //don't call c_str()
		return true;
	} catch (std::exception const &e) {
		return false;
	}
}

bool is_float(std::string str, float &val) {
	try {
		val = std::stof(str); //don't call c_str()
		return true;
	} catch (std::exception const &e) {
		return false;
	}
}

bool is_valid_date(std::string &str) {
	int n;
	const char *c = str.c_str();
	if (str.length() == 16)
		return is_int(str.substr(0, 4), n) && (c[4] == '-') && (c[7] == '-')
				&& (c[10] == '-') && (c[13] == ':')
				&& is_int(str.substr(5, 2), n) && is_int(str.substr(8, 2), n)
				&& is_int(str.substr(11, 2), n) && is_int(str.substr(14, 2), n);
	else
		return false;
}

string commands[] = { "help", "contact", "c", "node", "chance", "mark", "rule",
		"save", "load", "printall", "delcontact", "d", "exit" };
/** Description of commands.
 * 	NOTE: Size of array must be equal to size of commands array.
 */
string descriptions[] =
		{ "This page.",
				"Shows or adds contact info between two nodes. Adds a new node if one in the contact doesn't exist.\n\tFormat: \"contact <id node1> <id node2>\" to show contact info\n\tFormat: \"contact <id node1> <id node2> <distance> <exposure (minutes) > <date (yyyy-MM-dd-hh:mm) >\" to add a new contact.",
				"Shorthand for \"contact\"",
				"Shows or adds node info to the Graph\n\tFormat: \"node <node id>\" to show data \n\tFormat: \"node <node id> <type>\" to add a node",
				"Shows infection chance of a node. Type \"chance all\" to show all nodes",
				"Marks infected / clean.\n\tFormat: \"mark <node id> <0/1>\" 0 -> clean, 1 -> infected",
				"Selects the rule.\n\tFormat: \"rule <index>\" index is 0, 1, 2.. refer to manual for correspondence",
				"Saves to file.\n\tFormat \"save <filename>\"",
				"Loads file.\n\tFormat \"load <filename>\"",
				"Prints chance of all nodes",
				"Deletes a contact.\n\tFormat: \"delcontact <node id 1> <node id 2>\"",
				"Shorthand for delcontact", "Quits the program" };

/** Placeholder for quitting the program */
void command_exit(Bundle args) {

}

/** Prints the whole graph */
void command_printall(Bundle args) {
	g.printall(cout);
}

/** Saves data to file */
void command_save(Bundle args) {
	ofstream of;
	of.open(args[1]);
	if (of.good())
		of << g;
	else
		cout << "Couldn't save data" << std::endl;
	of.close();
}

void command_load(Bundle args) {
	ifstream in;
	in.open(args[1]);
	if (in.good())
		in >> g;
	else
		cout << "Couldn't load data" << std::endl;
	in.close();

	// Before applying any rule, we must reset data first (infection 1 and 0)
	g.apply_rule(rules[3]);
	g.apply_rule(rule);
}

void command_rule(Bundle args) {
	int n;
	if (!is_int(args[1], n)) {
		cout << "Invalid rule\n";
		return;
	}
	if ((unsigned) n >= sizeof(rules) / sizeof(Rule)) {
		cout << "Invalid index.\n";
		return;
	}
	rule = rules[n];
	// Before applying any rule, we must reset data first (infection 1 and 0)
	g.apply_rule(rules[3]);
	g.apply_rule(rule);
}

void command_mark(Bundle args) {
	if (args.size != 3) {
		cout << "Incorrect number of arguments. See help section.\n";
		return;
	}

	int n;
	if (!is_int(args[2], n)) {
		cout << "Invalid value. 1 -> infected\t 0 -> clear\n";
		return;
	}

	if (g.node_exists(args[1])) {
		g.mark_infected(args[1], n);
	} else {
		cout << "Invalid node\n";
	}
	// Before applying any rule, we must reset data first (infection 1 and 0)
	g.apply_rule(rules[3]);
	g.apply_rule(rule);
}

/** Shows or adds node to Graph */
void command_chance(Bundle args) {
	if (args.size == 2) {
		if (g.node_exists(args[1])) {
			print_chance(args[1]);
		} else {
			cout << "Invalid node\n";
		}
	} else {
		cout << "Incorrect number of arguments. See help section.\n";
	}

}

/** Shows or adds node to Graph */
void command_node(Bundle args) {
	if (args.size == 3 || args.size == 2) {
		int n = 0;
		if (args.size == 3)
			if (!is_int(args[2].c_str(), n)) {
				cout
						<< "Invalid value. Refer to manual for node types or leave empty\n";
				return;
			}

		if (!g.node_exists(args[1])) {
			g.add_node(
					Node::NodeFactory().set_id(args[1]).set_type(n).getNode());
		}
	} else {
		cout << "Incorrect number of arguments. See help section.\n";
		return;
	}
}

void command_delcontact(Bundle args) {
	int argnum = args.size - 1;
	if (argnum != 2) {
		cout << "Incorrect number of arguments. See help section." << endl;
		return;
	}

	if (argnum == 2) {
		if (g.node_exists(args[1]) && g.node_exists(args[2])) {
			g.delete_contact(args[1], args[2]);
		} else {
			cout << "Cannot delete contact with nonexistent node\n";
		}
	}

}

/** Shows or adds contact to Graph */
void command_contact(Bundle args) {
	int argnum = args.size - 1;
	if (argnum != 2 && argnum != 5 && argnum != 4) {
		cout << "Incorrect number of arguments. Try again" << endl;
		return;
	}

	if (argnum == 2) {
		g.print_contact(args[1], args[2], cout);
	} else {

		float distance, exposure;

		if (!is_float(args[3], distance)) {
			cout << "Invalid distance\n";
			return;
		}
		if (!is_float(args[4], exposure)) {
			cout << "Invalid exposure\n";
			return;
		}
		if (!is_valid_date(args[5])) {
			cout << "Invalid date\n";
			return;
		}

		if (!g.node_exists(args[1])) {
			g.add_node(Node::NodeFactory().set_id(args[1]).getNode());
		}
		if (!g.node_exists(args[2])) {
			g.add_node(Node::NodeFactory().set_id(args[2]).getNode());
		}

		g.add_contact(args[1], args[2], distance, exposure, args[5], rule);
	}

}

/** Outputs commands and their descriptions */
void command_help(Bundle args) {
	for (unsigned int i = 0; i < sizeof(commands) / sizeof(string); i++) {
		cout << commands[i] << ": " << descriptions[i] << endl;
	}
}

/** Finds index of command or returns index of help */
int findindex(string s) {
	for (unsigned int i = 0; i < sizeof(commands) / sizeof(string); i++)
		if (s == commands[i])
			return i;
	return 0;
}

/** Array of function pointers for commands */
void (*functions[])(
		Bundle args) = {command_help, command_contact, command_contact,
			command_node, command_chance, command_mark,
			command_rule, command_save, command_load,
			command_printall, command_delcontact, command_delcontact,
			command_exit};

/** Counts occurrences of character in char array */
unsigned int count_char(const char *s, int len, char c) {
	unsigned int count = 0;
	for (int i = 0; i < len; i++)
		if (s[i] == c)
			count++;
	return count;
}

/** Splits string in string[] by spaces */
Bundle split_args(string s) {
	const char *spl = string(" ").c_str();
	char *str = new char[90];
	std::strcpy(str, s.c_str());
	unsigned int count = count_char(s.c_str(), s.length(), ' ') + 1;
	string *args = new string[count];
	char *tok = std::strtok(str, spl);
	int c = 0;
	while (tok != NULL) {
		args[c++] = string(tok);
		tok = std::strtok(NULL, spl);
	}
	delete[] str;
	return Bundle { args, count };
}

void sendcommand() {
	char in[256];
	do {
		cout << "Command > ";
		cin.getline(in, 255);
		Bundle args = split_args(in);
		functions[findindex(args[0])](args);
		delete[] args.data;
	} while (std::strcmp(in, "exit") != 0);
}

