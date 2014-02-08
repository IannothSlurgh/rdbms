#ifndef ENTITY_GUARD
#define ENTITY_GUARD
#include <vector>
#include "attribute.h"

using namespace std;

class entity
{
	vector <attribute *> attribute_list; //Polymorphic pointers
public:
	entity(){};
	void addIntAttribute(int num_value);
	void addStringAttribute(string str_value);
	attribute getAttribute(int index);
};
#endif
