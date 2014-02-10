
#ifndef ENTITY_GUARD
#define ENTITY_GUARD
#include <vector>
#include "attribute.h"

using namespace std;

class entity
{
	vector<attribute> attribute_list; //Polymorphic pointers

public:
	entity(){};
	//~entity() Make sure to delete all the pointers in the attribute_list
	void addIntAttribute(int num_value);
	void addStringAttribute(string str_value, int str_length);
	attribute getAttribute(int index);//Make sure to make deep copy, passing new dynamic memory pointer, 
	//and then tell the user of this function to delete the pointer.
};
#endif
