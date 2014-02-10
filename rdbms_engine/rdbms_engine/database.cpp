#include "Database.h"

Database::Database(){

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

//Assumed that Union compatible means has same rows.
/*table setUnion(table table_one, table table_two)
{
	int one_num_columns = table_one.numColumns();
	int two_num_columns = table_two.numColumns();
	vector <unsigned int> one_primary_keys;
	vector <unsigned int> two_primary_keys;
	one_primary_keys = table_one.getPrimaryKeys();
	two_primary_keys = table_two.getPrimaryKeys();
	if(one_num_columns != two_num_columns)
	{
		table non_union_compatible;
		non_union_compatible.error_code = ERR_TOO_MANY_COLUMNS;
		return non_union_compatible;
	}
	if(one_primary_keys != two_primary_keys)
	{
		table non_union_compatible;
		non_union_compatible.error_code = ERR_PRIMARY_KEY_MISMATCH;
		return non_union_compatible;
	}
	int one_num_entities = table_one.numEntities();
	int two_num_entities= table_two.numEntities();
	vector <unsigned int> black_list_entities; //indices of duplicates in table_two
	for(unsigned int i = 0; i<one_num_entities; ++i)
	{
		one_primary_keys = table_one.getPrimaryKeys();
		for(unsigned int j = 0; j<two_num_entities;++j)
		{
			
			if()
		}
	}
}*/

