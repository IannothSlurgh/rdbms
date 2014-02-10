#include "entity.h"

void entity::addIntAttribute(int num_value){
	int_attribute new_attribute(num_value);
	attribute_list.push_back(new_attribute);
}

void entity::addStringAttribute(string str_value, int str_length){
	string_attribute new_attribute(str_value, str_length);
	attribute_list.push_back(new_attribute);
}

attribute entity::getAttribute(int index){
	return attribute_list[index];
}