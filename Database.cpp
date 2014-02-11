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

table project(vector<string> attr_list, table source_table){
	string table_name = "project table"; // Default temporary name. Will be changed later
	vector<unsigned int> pk = source_table.getPrimaryKeys();
	vector<unsigned int> ct = source_table.getColumnTypes();
	vector<string> cn = source_table.getColumnNames();
	vector<entity> el = source_table.getEntityList();

	vector<string> new_column_names;
	vector<unsigned int> new_column_types;
	vector<unsigned int> new_pk;
	unsigned int count = 0;

	for(unsigned int i = 0; i < attr_list.size(); i++){     // Itterate through the attr_list
		for(unsigned int k = 0; k < cn.size(); k++){        // Itterate through the column name list
			if(cn[k] == attr_list[i]){                      // Check if they are equal
				new_column_names.push_back(attr_list[i]);   // Push back everything about the column into new vectors
				new_column_types.push_back(ct[k]);
				new_pk.push_back(count);
				count++;                                    // Increment count for primary keys
			}
		}
	}

	table new_table(table_name, new_column_names, new_column_types, new_pk); // Create table with new values

	for(unsigned int i = 0; i < el.size(); i++){            // Itterate through the entity list
		entity new_entity;
		for(unsigned int j = 0; j < cn.size(); j++){        // Itterate though the column name list
			if(attr_list[j] == source_table.getAttributeColumn(cn[j]).getColumnName()){
				int attr_index = source_table.getAttributeColumn(cn[j]);	// Get the index of the attribute
				attribute new_attr = el[i].getAttribute(attr_index);		// Create a new attribute with the correct properties
				int type = ct[j];
				if(type == 0){
					new_entity.addIntAttribute(new_attr.get_int_value());	// Add to entity if it is an int
				}
				if(type == 1){                                              // Add to entity if it is a string
					new_entity.addStringAttribute(new_attr.get_string_value(), new_attr.get_length());
				}
			}
		}
		new_table.addEntity(new_entity);	// Add the entity to the table
	}
	return new_table;
}

table crossProduct(table table_one, table table_two){
	vector<unsigned int> ct_one = table_one.getColumnTypes();
	vector<unsigned int> ct_two = table_two.getColumnTypes();
	vector<unsigned int> pk_one = table_one.getPrimaryKeys();
	vector<unsigned int> pk_two = table_two.getPrimaryKeys();
	vector<string> cn_one = table_one.getColumnNames();
	vector<string> cn_two = table_two.getColumnNames();
	vector<entity> el_one = table_one.getEntityList();
	vector<entity> el_two = table_two.getEntityList();

	vector<unsigned int> new_column_types;
	vector<unsigned int> new_primary_keys;
	vector<string> new_column_names;

	for(unsigned int i = 0; i < ct_one.size(); i++)	// Add first table's column types to the column vector
	{
		new_column_types.push_back(ct_one[i]);
	}
	for(unsigned int i = 0; i < ct_two.size(); i++) // Add second table's column types to the column vector
	{
		new_column_types.push_back(ct_two[i]);
	}
	for(unsigned int i = 0; i < pk_one.size(); i++)	// Add first table's primary keys to the pk vector
	{
		new_primary_keys.push_back(pk_one[i]);
	}
	for(unsigned int i = 0; i < pk_two.size(); i++) // Add second table's primary keys to the pk vector
	{
		new_primary_keys.push_back(pk_two[i]+pk_one.size());
	}
	for(unsigned int i = 0; i < cn_one.size(); i++)	// Add first table's column names to the name vector
	{
		new_column_names.push_back(cn_one[i]);
	}
	for(unsigned int i = 0; i < cn_two.size(); i++)	// Add second table's column names to the name vector
	{
		string renamed = cn_two[i]+"$";	// Add identifier to have a difference between the original tables
		new_column_names.push_back(renamed);
	}
	string table_name = "cross product table";	// Generic name
	table new_table(table_name, new_column_names, new_column_types, new_primary_keys);

	for(unsigned int i = 0; i < el_one.size(); i++){ // Itterate through first entity list
		for(unsigned int k = 0; k < el_two.size(); k++){ // Itterate through second entity list
			el_one[i].merge(el_two[k]);					 // Merge the first entity's attributes with the second
			new_table.addEntity(el_one[i]);				 // Add the newly created entity to the table
		}
	}
	return new_table;
}

table naturalJoin(table table_one, table table_two){
	string table_name = "natural join table";
	vector<string> table_one_column_names = table_one.getColumnNames();
	vector<string> table_two_column_names = table_two.getColumnNames();
	vector<unsigned int> table_one_column_types = table_one.getColumnTypes();
	vector<unsigned int> table_two_column_types = table_two.getColumnTypes();
	vector<entity> table_one_entity_list = table_one.getEntityList();
	vector<entity> table_two_entity_list = table_two.getEntityList();

	vector<unsigned int> new_column_types;
	vector<entity> new_table_entities;
	vector<string> new_table_column_names;
	vector<entity> final_table_entities;

	for(int i = 0; i < table_one_column_names.size(); i++){   // Add all column names, types, and entities into combined vectors
		new_table_column_names.push_back(table_one_column_names[i]);
	}
	for(int k = 0; k < table_two_column_names.size(); k++){
		new_table_column_names.push_back(table_two_column_names[k]);
	}
	for(int i = 0; i < table_one_column_types.size(); i++){
		new_table_column_types.push_back(table_one_column_types[i]);
	}
	for(int k = 0; k < table_two_column_types.size(); k++){
		new_table_column_types.push_back(table_two_column_types[k]);
	}
	for(int i = 0; i < table_one_entity_list.size(); i++){
		new_table_entities.push_back(table_one_entity_list[i]);
	}
	for(int k = 0; k < table_two_entity_list.size(); k++){
		new_table_entities.push_back(table_two_entity_list[k]);
	}

	vector<int> removed_indexes;

	for(int i = 0; i < table_one_column_names.size(); i++){ // Delete Repeated columns
		for(int k = 0; k < table_two_column_names.size(); k++){
			if(table_one_column_names[i] == table_two_column_names[k]){
				int index = i+table_two_column_names.size();
				removed_indexes.push_back(index); // Store removed indexes
			}
		}
	}
	for(int i = 0; i < removed_indexes.size(); i++){   // Remove repeated indexes
		int index = removed_indexes[i];
		new_table_column_names.erase(new_table_column_names.begin()+index);
		new_table_column_types.erase(new_table_column_types.begin()+index);
	}
	for(int i = 0; i < new_table_entities.size(); i++){ // Add entities not in the deleted columns
		entity e;
		for(int k = 0; k < removed_indexes.size(); k++){
			if(removed_indexes[k] == i){
				// Do Nothing
			}
			else{
				attribute a = new_table_entities[i];
				e.addAttribute(a);
			}
		}
		final_table_entities.push_back(e);
	}
	
	vector<unsigned int> new_table_primary_keys;
	unsigned int count = 0;
	for(int i = 0; i < new_table_column_names.size(); i++){  // Make Primary Key
		new_table_primary_keys.push_back(count);
		count++;
	}
	
	table final_table(table_name, new_column_names, new_column_types, new_table_primary_keys);
	return final_table;
}