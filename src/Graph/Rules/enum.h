/*
 * enum.h
 *
 *  Created on: 22 dic 2021
 *      Author: arocc
 */

#ifndef GRAPH_RULES_ENUM_H_
#define GRAPH_RULES_ENUM_H_

/** Used for serialization/deserialization */
static const char* divider_node = "+";
static const char* divider_contact = ";";

enum nodetype{
	node = 0,
	person = 1,
	building = 2
};


#endif /* GRAPH_RULES_ENUM_H_ */
