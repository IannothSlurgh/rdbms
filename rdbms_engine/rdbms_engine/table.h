#ifndef TABLE_GUARD
#define TABLE_GUARD

#include "entity.h"

class table
{
	vector <entity> entity_list;
	vector <string> column_names;
public:
	string name;
	table();
};

#endif
