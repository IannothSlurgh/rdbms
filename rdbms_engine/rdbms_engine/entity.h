#ifndef ENTITY_GUARD
#define ENTITY_GUARD
#include <vector>
#include "attribute.h"

using namespace std;

class entity
{
private:
	vector<attribute> attribute_list;
public:
	entity(){};
	void addIntAttribute(int num_value);
	void addStringAttribute(string str_value);
	void addAttribute(attribute new_attribute);
	attribute getAttribute(int index);
	int getNumOfAttributes();
	void merge(entity another_entity);
	void emptyAttributeList();
	void setAttributeAt(int index, attribute new_attribute);
};

bool operator==(entity& e1, entity& e2);

#endif
