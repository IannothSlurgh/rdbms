#include "entity.h"



void entity::addIntAttribute(int num_value){
	attribute new_attribute(num_value);
	attribute_list.push_back(new_attribute);
}

void entity::addStringAttribute(string str_value, int str_length){
	attribute new_attribute(str_value, str_length);
	attribute_list.push_back(new_attribute);
}

attribute entity::getAttribute(int index){
	return attribute_list[index];
}

void entity::addAttribute(attribute new_attribute){
	attribute_list.push_back(new_attribute);
}

int entity::getNumOfAttributes(){
	return attribute_list.size();
}

void entity::merge(entity another_entity){
	for(int i = 0; i < another_entity.getNumOfAttributes(); i++){
		addAttribute(another_entity.getAttribute(i));
	}
}

void entity::emptyAttributeList(){
	attribute_list.erase(attribute_list.begin(), attribute_list.end());
}

void entity::setAttributeAt(int index, attribute new_attribute){
	attribute_list[index] = new_attribute;
}

bool operator==(entity& e1, entity& e2){
	if(e1.getNumOfAttributes() != e2.getNumOfAttributes()){
		return false;
	}

	for(int i = 0; i < e1.getNumOfAttributes(); i++){
		if(!(e1.getAttribute(i) == e2.getAttribute(i))){
			return false;
		}
	}
	return true;
}