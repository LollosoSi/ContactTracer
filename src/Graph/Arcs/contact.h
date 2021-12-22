/*
 * contact.h
 *
 *  Created on: 21 dic 2021
 *      Author: arocc
 */

#pragma once

//#include "../node.h"
class Node;

#include <string>

using namespace std;

/** Describes contact between two nodes */
class Contact {
public:
	/** Constructor
	 *
	 */
	Contact() {
	}
	;

	/** Constructor
	 * @brief sets all the basic components
	 * @param distance The minimum distance within contact took place
	 * @param exposure Time of exposure, in minutes
	 * @param date Date+time of contact
	 * @param n1, n2 Nodes to be linked
	 * @author Andrea
	 */
	Contact(float distance, float exposure, string date, Node *n1, Node *n2) {
		update(distance, exposure, date);
		first = n1;
		second = n2;
	}

	/**
	 * @brief updates the basic components
	 * @param distance The minimum distance within contact took place
	 * @param exposure Time of exposure, in minutes
	 * @param date Date+time of contact
	 * @author Andrea
	 */
	void update(float distance, float exposure, string date) {
		this->distance = distance;
		this->exposure = exposure;
		this->date = date;
	}

	/** Destructor */
	virtual ~Contact();

	/**
	 * @returns first if second is passed, second if first is passed, otherwise nullptr
	 * @author Andrea
	 */
	Node* get_other_node(Node *n) const {
		return n == first ? second : n == second ? first : nullptr;
	}
	//Node* get_higher_chance_node(){return (first->get_infection_chance()-second->get_infection_chance()) <= 0 ? nullptr : first->get_infection_chance()>second->get_infection_chance() ? first : second; }

	/**
	 * @param n number of node. Accepted range {0, 1}
	 * @returns first if n == 0, second if n == 1 or nullptr
	 */
	Node* get_node(int n = 0) const {
		return !n ? first : n == 1 ? second : nullptr;
	}

	/* Nodes to be linked */
	Node *first = nullptr, *second = nullptr;

protected:
	// Meters
	float distance = 0;
	// Minutes
	float exposure = 0;
	// Date. Format aaaa-mm-dd HH:MM
	string date = "0000-00-00 00:00";
};

