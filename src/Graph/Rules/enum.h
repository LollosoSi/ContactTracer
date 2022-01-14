/*
 * enum.h
 *
 *  Created on: 22 dic 2021
 *      Author: arocc
 */

#pragma once

/** Used for serialization/deserialization */
static const char* divider_node = "+";
static const char* divider_contact = ";";

enum nodetype{
	node = 0,
	person = 1,
	building = 2
};

