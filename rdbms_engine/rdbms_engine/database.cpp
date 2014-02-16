#include "Database.h"

Database::Database(){

}

table Database::findTable(string table_name){
	for(unsigned int i = 0; i < table_list.size(); i++){
		if(table_list[i].getName().compare(table_name)){
			return table_list[i];
		}
	}
	return table();
}

void Database::createTable(string table_name, vector<string> attribute_names, vector<unsigned int> attr_types, vector<unsigned int> primary_key){
	table new_table(table_name, attribute_names, attr_types, primary_key);
	table_list.push_back(new_table);
}

void Database::dropTable(string table_name){
	for(unsigned int i = 0; i < table_list.size(); i++){
		if(table_list[i].getName().compare(table_name) == 0){
			table_list.erase(table_list.begin() + i);
		}
	}
}

void Database::deleteFromTable(string table_name, Condition condition){
	table target_table = findTable(table_name);
	for(unsigned int i = 0; i < table_list.size(); i++){
		if(condition.result(i)){
			target_table.removeEntity(i);
		}
	}
}

void Database::insertIntoTable(string table_name, table source_table){
	table destination_table = findTable(table_name);
	for(int i = 0; i < source_table.getNumOfEntities(); i++){
		entity temp_entity = source_table.getEntityAt(i);
		destination_table.addEntity(temp_entity);
	}
}

void Database::insertIntoTable(string table_name, vector<attribute> attr_list){
	table destination_table = findTable(table_name);
	//make sure size of columns is equal to attr_list
	entity new_entity;
	for(unsigned int i = 0; i < attr_list.size(); i++){
		attribute new_attribute = attr_list[i];
		new_entity.addAttribute(new_attribute);
	}

	destination_table.addEntity(new_entity);
}

table Database::select(Condition condition, table source_table){
	table new_table("", source_table.getColumnNames(), source_table.getColumnTypes(), source_table.getPrimaryKeys());
	for(int i = 0; i < source_table.getNumOfEntities(); i++){
		if(condition.result(i)){
			new_table.addEntity(source_table.getEntityAt(i));
		}
	}
	return new_table;
}

void Database::updateEntity(string table_name, vector<string> attr_names, vector<attribute> attr_literals, Condition condition){
	table target_table = findTable(table_name);
	for(int i = 0; i < target_table.getNumOfEntities(); i++){
		if(condition.result(i)){
			entity changed_entity = target_table.getEntityAt(i);
			for(unsigned int j = 0; j < attr_names.size(); j++){
				int col_index = target_table.getAttributeColumn(attr_names[j]);
				changed_entity.setAttributeAt(col_index, attr_literals[j]);
			}
			target_table.setEntityAt(i, changed_entity);
		}
	}
}

table Database::project(vector<string> attr_list, table source_table){
	string table_name = "project table"; // Default temporary name. Will be changed later
	vector<unsigned int> pk = source_table.getPrimaryKeys();
	vector<unsigned int> ct = source_table.getColumnTypes();
	vector<string> cn = source_table.getColumnNames();
	vector<entity> el = source_table.getEntityList();

	vector<string> new_column_names;
	vector<unsigned int> new_column_types;
	table new_table(table_name, cn, ct, pk); //shouldn't attr_list be used instead of cn

	for(unsigned int i = 0; i < el.size(); i++){
		entity new_entity;
		for(unsigned int j = 0; j < cn.size(); j++){//i think you need to use attr_list instead of cn
			int attr_index = source_table.getAttributeColumn(cn[j]);
			attribute new_attr = el[i].getAttribute(attr_index);
			int type = ct[j];
			if(j == 0){
				new_entity.addIntAttribute(new_attr.get_int_value());
			}
			if(j == 1){
				new_entity.addStringAttribute(new_attr.get_string_value(), new_attr.getLength());
			}
		}
		new_table.addEntity(new_entity);
	}
	return new_table;
}

table Database::crossProduct(table table_one, table table_two){
	vector<unsigned int> ct1 = table_one.getColumnTypes();
	vector<unsigned int> ct2 = table_two.getColumnTypes();
	vector<unsigned int> pk1 = table_one.getPrimaryKeys();
	vector<unsigned int> pk2 = table_two.getPrimaryKeys();
	vector<string> cn1 = table_one.getColumnNames();
	vector<string> cn2 = table_two.getColumnNames();
	vector<entity> el1 = table_one.getEntityList();
	vector<entity> el2 = table_two.getEntityList();

	vector<unsigned int> new_column_types;
	vector<unsigned int> new_primary_keys;
	vector<string> new_column_names;

	for(unsigned int i = 0; i < ct1.size(); i++)
	{
		new_column_types.push_back(ct1[i]);
	}
	for(unsigned int i = 0; i < ct2.size(); i++)
	{
		new_column_types.push_back(ct2[i]);
	}
	for(unsigned int i = 0; i < pk1.size(); i++)
	{
		new_primary_keys.push_back(pk1[i]);
	}
	for(unsigned int i = 0; i < pk2.size(); i++)
	{
		new_primary_keys.push_back(pk2[i]);
	}
	for(unsigned int i = 0; i < cn1.size(); i++)
	{
		new_column_names.push_back(cn1[i]);
	}
	for(unsigned int i = 0; i < cn2.size(); i++)
	{
		string renamed = cn2[i]+"$";
		new_column_names.push_back(renamed);
	}
	string table_name = "cross product table";
	table new_table(table_name, new_column_names, new_column_types, new_primary_keys);

	for(unsigned int i = 0; i < el1.size(); i++){
		entity new_entity;
		for(unsigned int k = 0; k < el2.size(); k++){
			el1[i].merge(el2[k]); //merge returns void, all the attributes stored in el2 are also stored in el1
			new_entity = el1[i];
			new_table.addEntity(new_entity);
		}
	}

	return new_table;
}

table Database::naturalJoin(table table_one, table table_two){
	table set_difference = setDifference(table_one, table_two);
	table set_union = setUnion(table_one, table_two);
	table final_table = crossProduct(set_difference, set_union);

	return final_table;
}

table rename(table original_table, string new_table_name, vector <string> new_column_names)
{
	table result = original_table;
	int original_num = original_table.numOfColumns();
	int new_num = new_column_names.size();
	if(new_num > original_num)
	{
		result.error_code = ERR_TOO_MANY_COLUMNS;
	}
	else
	{
		for(int i = 0; i<new_num; ++i)
		{
			result.renameColumn(new_column_names.at(i), i);
		}
	}
	return result;
}

/*table setUnion(table table_one, table table_two)
{
	int one_num_columns = table_one.numColumns();
	int two_num_columns = table_two.numColumns();
	if(one_num_columns != two_num_columns)
	{
		table non_union_compatible;
		non_union_compatible.error_code = ERR_TOO_MANY_COLUMNS;
		return non_union_compatible;
	}
	int one_num_entities = table_one.numEntities();
	int two_num_entities= table_two.numEntities();
	vector <unsigned int> black_list_entities; //indices of duplicates in table_two
	for(unsigned int i = 0; i<one_num_entities; ++i)
	{
		table_one.
		for(unsigned int j = 0; j<two_num_entities;++j)
		{
		}
	}
}*/
