#include "table.h"

table::table(){
	error_code = 0;
	is_query = false;
}

table::table(string n, vector<string> cn, vector<unsigned int> ct, vector<unsigned int> pk){
	name = n;
	column_types = ct;
	column_names = cn;
	primary_keys = pk;
	error_code = 0;
	is_query = false;
}

vector<unsigned int> table::getPrimaryKeys(){
	return primary_keys;
}

void table::setAsQuery(){
	is_query = true;
}

int table::getAttributeColumn(string column_name){
	for(unsigned int i = 0; i < column_names.size(); i++){
		if(column_name.compare(column_names[i]) == 0){
			return i;
		}
	}

	return -1;
}

void table::removeEntity(int entity_index){
	entity_list.erase(entity_list.begin() + entity_index);
}

entity table::getEntityAt(int index){
	return entity_list[index];
}

string table::getColumnName(int index){
	return column_names[index];
}

unsigned int table::getColumnTypeAt(int column_index){
	return column_types[column_index];
}

entity table::getEntityWith(vector<attribute> primary_key){
	for(unsigned int i = 0; i < entity_list.size(); i++){
		entity current_entity = entity_list[i];
		bool check = false;
		for(unsigned int j = 0; j < primary_keys.size(); j++){
			int key = primary_keys[j];
			attribute attr = current_entity.getAttribute(key);

			if(column_types[key] == INTEGER){
				check = (attr.get_int_value() == primary_key[j].get_int_value());
			}

			else if(column_types[key] == STRING){
				check = (attr.get_string_value() == primary_key[j].get_string_value());
			}

			if(!check){ break; }
		}

		if(check){
			return current_entity;
		}
	}

	return entity();
}

void table::renameColumn(string new_name, int index){
	column_names[index] = new_name;
}

string table::getName(){
	return name;
}

int table::getNumOfEntities(){
	return entity_list.size();
}

void table::addEntity(entity new_entity){
	//check attributes
	entity_list.push_back(new_entity);
}

int table::numOfColumns(){
	return column_names.size();
}

vector<unsigned int> table::getColumnTypes(){
	return column_types;
}

vector<string> table::getColumnNames(){
	return column_names;
}

vector<entity> table::getEntityList(){
	return entity_list;
}

void table::changeName(string new_name){
	name = new_name;
}

void table::setEntityAt(int index, entity new_entity){
	entity_list[index] = new_entity;
}

bool operator==(table& t1, table& t2){
	if(t1.getNumOfEntities() != t2.getNumOfEntities()){
		return false;
	}

	if(t1.numOfColumns() != t2.numOfColumns()){
		return false;
	}

	for(int i = 0; i < t1.numOfColumns(); i++){
		if(t1.getColumnNames()[i].compare(t2.getColumnNames()[i]) != 0 || t1.getColumnTypes()[i] != t2.getColumnTypes()[i]){
			return false;
		}
	}

	for(int j = 0; j < t1.getEntityList().size(); j++){
		if(!(t1.getEntityList()[j] == t2.getEntityList()[j])){
			return false;
		}
	}

	return true;
}