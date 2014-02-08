#ifndef TABLE_GUARD
#define TABLE_GUARD

#include "entity.h"

class table
{
	vector <entity> entity_list;
	vector <string> column_names;
	vector <unsigned int> column_types;
public:
	string name;
	table();
	entity listByAttribute(string attribute_name);
	
};

#endif
