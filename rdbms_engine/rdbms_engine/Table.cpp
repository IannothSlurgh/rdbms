#include "table.h"

table::table(){
	error_code = 0;
	is_query = false;
}

table::table(string n, vector<string> cn, vector<unsigned int> ct, vector<unsigned int> pk, vector<unsigned int> cw){
	name = n;
	column_types = ct;
	column_names = cn;
	primary_keys = pk;
	col_width = cw;
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

//ADD: check the primary keys to make sure that new_entity doesn't already exist in table
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

	for(unsigned int j = 0; j < t1.getEntityList().size(); j++){
		if(!(t1.getEntityList()[j] == t2.getEntityList()[j])){
			return false;
		}
	}

	return true;
}

bool table::checkQuery(){
	return is_query;
}

vector<unsigned int> table::getColumnWidths()
{
	return col_width;
}

ostream& operator<<(ostream& os, table& t)
{
	os << t.getName()  << endl;
	for(unsigned int g = 0; g < t.getColumnWidths().size(); g++)
	{
		os << to_string(t.getColumnWidths()[g]) << " ";
	}
	os << endl;

	for(unsigned int f = 0; f < t.getPrimaryKeys().size(); f++)
	{
		os << to_string(t.getPrimaryKeys()[f]) << " ";
	}
	os << endl;

	for(unsigned int e = 0; e < t.getColumnTypes().size(); e++)
	{
		os << to_string(t.getColumnTypes()[e]) << " ";
	}
	os << endl;

	for(unsigned int i = 0; i < t.getColumnNames().size(); i++)
	{
		os <<  t.getColumnNames()[i] << " ";
	}
	os << endl;

	os << t.getNumOfEntities() << endl;

	for(int j = 0; j < t.getNumOfEntities(); j++)
	{
		for(int h = 0; h < t.getEntityAt(j).getNumOfAttributes(); h++)
		{
			int attr_type =  t.getEntityAt(j).getAttribute(h).getType();
			os <<  t.getEntityAt(j).getAttribute(h).get_string_value() << " ";
		}
		os << endl;
	}
	return os;
}

istream& operator>>(istream& is, table& t)
{
	string table_name = "";
	getline(is, table_name);

	string temp_col_width;
	vector<unsigned int> col_width_list;
	while(getline(is, temp_col_width, ' '))
	{
		col_width_list.push_back(atoi(temp_col_width.c_str()));
	}

	string temp_p_keys = 0;
	vector<unsigned int> p_keys;
	while(getline(is, temp_p_keys, ' '))
	{
		p_keys.push_back(atoi(temp_p_keys.c_str()));
	}

	string temp_col_types = "";
	vector<unsigned int> col_types;
	while(getline(is, temp_col_types, ' '))
	{
		col_types.push_back(atoi(temp_col_types.c_str()));
	}

	unsigned int num_of_entities;
	is >> num_of_entities;

	string temp_col_names = "";
	vector<string> col_names_list;
	while(getline(is, temp_col_names, ' '))
	{
		col_names_list.push_back(temp_col_names);
	}
	
	table new_table(table_name, col_names_list, col_types, p_keys, col_width_list);

	for(unsigned int i = 0; i < num_of_entities; i--)
	{
		entity new_entity;
		
		for(unsigned int j = 0; j < col_types.size(); j++)
		{
			string line = "";
			getline(is, line, ' ');
			if(col_types[j] == STRING)
			{
				attribute new_attr(line);
				new_entity.addAttribute(new_attr);
			}
			else
			{
				attribute new_attr(atoi(line.c_str()));
				new_entity.addAttribute(new_attr);
			}
		}

		new_table.addEntity(new_entity);
	}

	t = new_table;
	return is;
}

const table& table::operator=(table &t)
{
	column_names = t.getColumnNames();
	column_types = t.getColumnTypes();
	primary_keys = t.getPrimaryKeys();
	col_width = t.getColumnWidths();
	is_query = t.checkQuery();
	name = t.getName();
	for(int i = 0; i < t.getNumOfEntities(); i++)
	{
		addEntity(t.getEntityAt(i));
	}
	return *this;
}

