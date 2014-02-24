#include "Database.h"

Database::Database(){
	is_finished = false;
}

void Database::execute(vector<string>& results, string command, Database& db)
{
	Parser new_parser(command, db, results);
}

//returns a reference to a table which has the same name as table_name
table& Database::findTable(string table_name){
	for(unsigned int i = 0; i < table_list.size(); i++){
		if(table_list[i].getName().compare(table_name) == 0){
			return table_list[i];
		}
	}
	return table(); //returns an empty table if it couldn't find the table_name
}

//adds a new table to the vector of tables
void Database::createTable(string table_name, vector<string> attribute_names, vector<unsigned int> attr_types, vector<unsigned int> primary_key, vector<unsigned int> column_lengths){
	table new_table(table_name, attribute_names, attr_types, primary_key, column_lengths);
	for(unsigned int i = 0; i < table_list.size(); i++){
		if(table_list[i].getName() == table_name){
			table_list[i] = new_table;
			return;
		}
	}
	table_list.push_back(new_table);
}

//removes a specific table from vector of tables
void Database::dropTable(string table_name){
	for(unsigned int i = 0; i < table_list.size(); i++){
		if(table_list[i].getName().compare(table_name) == 0){
			table_list.erase(table_list.begin() + i);
		}
	}
}

//removes an entity(s) from a specific table when the condition is true 
void Database::deleteFromTable(string table_name, Condition condition){
	table& target_table = findTable(table_name);
	vector<int> indexes_to_delete;
	for(int i = 0; i < target_table.getNumOfEntities(); i++){
		if(condition.result(i)){//condition is true, remove entity at position i
			indexes_to_delete.push_back(i); //once entity is removed, messes with size
		}
	}

	for(unsigned int j = 0; j < indexes_to_delete.size(); j++){
		int delete_index = indexes_to_delete[j] - j;
		target_table.removeEntity(delete_index);
	}
}

//inserts all the entities from source_table into the specified tabled
void Database::insertIntoTable(string table_name, table source_table){
	table& destination_table = findTable(table_name);
	for(int i = 0; i < source_table.getNumOfEntities(); i++){
		entity temp_entity = source_table.getEntityAt(i);
		destination_table.addEntity(temp_entity);
	}
	
}

//inserts a new entity into a table
void Database::insertIntoTable(string table_name, vector<attribute> attr_list){
	table& destination_table = findTable(table_name);
	//make sure size of columns is equal to attr_list
	entity new_entity;
	for(unsigned int i = 0; i < attr_list.size(); i++){
		attribute new_attribute = attr_list[i];
		new_entity.addAttribute(new_attribute);
	}
	destination_table.addEntity(new_entity);
}

//returns a table containing all the entities in the source_table that meet the specified condition
table Database::select(Condition condition, table source_table){
	table new_table("", source_table.getColumnNames(), source_table.getColumnTypes(), source_table.getPrimaryKeys(), source_table.getColumnWidths());
	for(int i = 0; i < source_table.getNumOfEntities(); i++){
		if(condition.result(i)){
			new_table.addEntity(source_table.getEntityAt(i));
		}
	}
	return new_table;
}

//changes the attributes of an entity in a table when the condition is true
void Database::updateEntity(string table_name, vector<string> attr_names, vector<attribute> attr_literals, Condition condition){
	table& target_table = findTable(table_name);
	for(int i = 0; i < target_table.getNumOfEntities(); i++){
		if(condition.result(i)){//condition is true
			entity changed_entity = target_table.getEntityAt(i);
			for(unsigned int j = 0; j < attr_names.size(); j++){//change an attribute in the entity
				int col_index = target_table.getAttributeColumn(attr_names[j]);
				changed_entity.setAttributeAt(col_index, attr_literals[j]);
			}
			target_table.setEntityAt(i, changed_entity); //add the new entity
		}
	}
}

table Database::project(vector<string> attr_list, table source_table){
	string table_name = "project table"; // Default temporary name. Will be changed later
	vector<unsigned int> pk = source_table.getPrimaryKeys();
	vector<unsigned int> ct = source_table.getColumnTypes();
	vector<string> cn = source_table.getColumnNames();
	vector<entity> el = source_table.getEntityList();
	vector<unsigned int> cw = source_table.getColumnWidths();

	vector<string> new_column_names;
	vector<unsigned int> new_column_types;
	vector<unsigned int> new_pk;
	vector<unsigned int> new_cw;
	vector<unsigned int> attr_indexes;
	unsigned int count = 0;

	for(unsigned int i = 0; i < attr_list.size(); i++){     // Itterate through the attr_list
		for(unsigned int k = 0; k < cn.size(); k++){        // Itterate through the column name list
			if(cn[k] == attr_list[i]){                      // Check if they are equal
				new_column_names.push_back(attr_list[i]);   // Push back everything about the column into new vectors
				new_column_types.push_back(ct[k]);
				new_pk.push_back(count);
				new_cw.push_back(cw[k]);
				attr_indexes.push_back(k);
				count++;                                    // Increment count for primary keys
			}
		}
	}

	table new_table(table_name, new_column_names, new_column_types, new_pk, new_cw); // Create table with new values

	for(unsigned int i = 0; i < el.size(); i++)
	{
		entity new_entity;
		for(unsigned int k = 0; k < attr_indexes.size(); k++)
		{
			new_entity.addAttribute(el[i].getAttribute(attr_indexes[k]));
		}
		new_table.addEntity(new_entity);
	}
	return new_table;
}

table Database::crossProduct(table table_one, table table_two){
	vector<unsigned int> ct_one = table_one.getColumnTypes();
	vector<unsigned int> ct_two = table_two.getColumnTypes();
	vector<unsigned int> pk_one = table_one.getPrimaryKeys();
	vector<unsigned int> pk_two = table_two.getPrimaryKeys();
	vector<unsigned int> cw_one = table_one.getColumnWidths();
	vector<unsigned int> cw_two = table_two.getColumnWidths();
	vector<string> cn_one = table_one.getColumnNames();
	vector<string> cn_two = table_two.getColumnNames();
	vector<entity> el_one = table_one.getEntityList();
	vector<entity> el_two = table_two.getEntityList();

	vector<unsigned int> new_column_types;
	vector<unsigned int> new_primary_keys;
	vector<unsigned int> new_column_widths;
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
		string renamed = cn_two[i];	// Add identifier to have a difference between the original tables
		//removed the identifier, was inferring with advanced query
		new_column_names.push_back(renamed);
	}
	for(unsigned int i = 0; i < cw_one.size(); i++)
	{
		new_column_widths.push_back(cw_one[i]);
	}
	for(unsigned int i = 0; i < cw_two.size(); i++)
	{
		new_column_widths.push_back(cw_two[i]);
	}
	string table_name = "cross product table";	// Generic name
	table new_table(table_name, new_column_names, new_column_types, new_primary_keys, new_column_widths);

	for(unsigned int i = 0; i < el_one.size(); i++){ // Itterate through first entity list
		entity new_entity;
		for(unsigned int k = 0; k < el_two.size(); k++){ // Itterate through second entity list
			el_one[i].merge(el_two[k]);	 // Merge the first entity's attributes with the second
			new_table.addEntity(el_one[i]);			 // Add the newly created entity to the table
		}
	}

	return new_table;
}

table Database::naturalJoin(table table_one, table table_two){
	string table_name = "natural join table";
	vector<string> table_one_column_names = table_one.getColumnNames();
	vector<string> table_two_column_names = table_two.getColumnNames();
	vector<unsigned int> table_one_column_types = table_one.getColumnTypes();
	vector<unsigned int> table_two_column_types = table_two.getColumnTypes();
	vector<entity> table_one_entity_list = table_one.getEntityList();
	vector<entity> table_two_entity_list = table_two.getEntityList();
	vector<unsigned int> table_one_column_widths = table_one.getColumnWidths();
	vector<unsigned int> table_two_column_widths = table_two.getColumnWidths();

	vector<unsigned int> new_table_column_types;
	vector<unsigned int> new_table_column_widths;
	vector<entity> new_table_entities;
	vector<string> new_table_column_names;
	vector<entity> final_table_entities;

	cout << table_one<<"\n";
	cout << table_two<<"\n";

	for(unsigned int i = 0; i < table_one_column_names.size(); i++){   // Add all column names, types, and entities into combined vectors
		new_table_column_names.push_back(table_one_column_names[i]);
	}
	for(unsigned int k = 0; k < table_two_column_names.size(); k++){
		new_table_column_names.push_back(table_two_column_names[k]);
	}
	for(unsigned int i = 0; i < table_one_column_types.size(); i++){
		new_table_column_types.push_back(table_one_column_types[i]);
	}
	for(unsigned int k = 0; k < table_two_column_types.size(); k++){
		new_table_column_types.push_back(table_two_column_types[k]);
	}
	for(unsigned int i = 0; i < table_one_entity_list.size(); i++){
		new_table_entities.push_back(table_one_entity_list[i]);
	}
	for(unsigned int k = 0; k < table_two_entity_list.size(); k++){
		new_table_entities.push_back(table_two_entity_list[k]);
	}
	for(unsigned int i = 0; i < table_one_column_widths.size(); i++){
		new_table_column_widths.push_back(table_one_column_widths[i]);
	}
	for(unsigned int k = 0; k < table_two_column_widths.size(); k++){
		new_table_column_widths.push_back(table_two_column_widths[k]);
	}

	vector<int> removed_indexes;

	for(unsigned int i = 0; i < table_one_column_names.size(); i++){ // Delete Repeated columns
		for(unsigned int k = 0; k < table_two_column_names.size(); k++){
			if(table_one_column_names[i] == table_two_column_names[k]){
				//int index = i+table_two_column_names.size();
				int index = k+table_one_column_names.size();
				removed_indexes.push_back(index); // Store removed indexes
			}
		}
	}
	for(unsigned int i = 0; i < removed_indexes.size(); i++){   // Remove repeated indexes
		int index = removed_indexes[i];
		new_table_column_names.erase(new_table_column_names.begin()+index-i);
		new_table_column_widths.erase(new_table_column_widths.begin()+index-i);
		new_table_column_types.erase(new_table_column_types.begin()+index-i);
	}
	/*for(unsigned int i = 0; i < new_table_entities.size(); i++){ // Add entities not in the deleted columns
		entity e;
		for(unsigned int k = 0; k < removed_indexes.size(); k++){
			if(removed_indexes[k] == i){
				// Do Nothing
			}
			else{
				attribute a = new_table_entities[i].getAttribute(i);
				e.addAttribute(a);
			}
		}
		final_table_entities.push_back(e);
	}*/
	
	for(unsigned int i = 0; i < new_table_entities.size(); i++){ // Add entities not in the deleted columns
		entity e;
		for(unsigned int j = 0; j < new_table_entities[i].getNumOfAttributes(); j++)
		{
			for(unsigned int k = 0; k < removed_indexes.size(); k++){
				if(removed_indexes[k] == j){
					// Do Nothing
				}
				else{
					attribute a = new_table_entities[i].getAttribute(j);
					e.addAttribute(a);
				}
			}
		}
		final_table_entities.push_back(e);
	}

	vector<unsigned int> new_table_primary_keys;
	unsigned int count = 0;
	for(unsigned int i = 0; i < new_table_column_names.size(); i++){  // Make Primary Key
		new_table_primary_keys.push_back(count);
		count++;
	}
	
	table final_table(table_name, new_table_column_names, new_table_column_types, new_table_primary_keys, new_table_column_widths);

	for(unsigned int i = 0; i < final_table_entities.size(); i++)
	{
		final_table.addEntity(final_table_entities[i]);
	}

	return final_table;
}

table Database::rename(vector <string> new_column_names, table original_table)
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

//Both tables have same columns and primary keys, but order of locations can differ.
table Database::setUnion(table table_one, table table_two)
{
	unsigned int one_num_columns = table_one.numOfColumns();
	unsigned int two_num_columns = table_two.numOfColumns();
	unsigned int one_key = 0;
	unsigned int two_key = 0;
	vector <unsigned int> one_primary_keys;
	vector <unsigned int> two_primary_keys;
	one_primary_keys = table_one.getPrimaryKeys();
	two_primary_keys = table_two.getPrimaryKeys();
	bool primary_keys_match = false;
	map<unsigned int, unsigned int> same_columns;
	//Check that two tables have same columns.
	if(one_num_columns != two_num_columns)
	{
		table non_union_compatible;
		non_union_compatible.error_code = ERR_TOO_MANY_COLUMNS;
		return non_union_compatible;
	}
	//Cycle through all column names, and map the same ones together. If not same, explode.
	for(unsigned int i = 0; i<one_num_columns; ++i)
	{
		string one_col_name = table_one.getColumnName(i);
		same_columns[i]=two_num_columns; //A number that is guaranteed not to be valid index
		for(unsigned int j = 0; j<two_num_columns; ++j)
		{
			string two_col_name = table_two.getColumnName(j);
			if(one_col_name == two_col_name)
			{
				same_columns[i]=j;
			}
		}
		if(same_columns[i]==two_num_columns) //A column did not match. Column mismatch.
		{
			table non_union_compatible;
			non_union_compatible.error_code = ERR_COLUMN_MISMATCH;
			return non_union_compatible;			
		}
	}
	//Since column mismatch did not occur and num columns same- can check all indices safely
	for(unsigned int i = 0; i < one_primary_keys.size(); ++i)
	{
		one_key = one_primary_keys.at(i);
		for(unsigned int j = 0; j < two_primary_keys.size(); ++j)
		{
			two_key = two_primary_keys.at(j);
			if(same_columns[one_key] == two_key)
			{
				primary_keys_match = true;
			}
		}
		if(primary_keys_match)
		{
			primary_keys_match = false;
		}
		else //Tables don't share the same keys.
		{
			table non_union_compatible;
			non_union_compatible.error_code = ERR_PRIMARY_KEY_MISMATCH;
			return non_union_compatible;			
		}
	}

	//Table is now verified as valid. If duplicate entities in between two tables, take table_one entity.
	
	int one_num_entities = table_one.getNumOfEntities();
	int two_num_entities = table_two.getNumOfEntities();
	vector <unsigned int> black_list_entities; //indices of duplicates in table_two
	vector <string> column_names;
	vector <unsigned int> column_types;
	entity entity_one;
	entity entity_two;
	for(unsigned int i = 0; i<one_num_columns;++i)
	{
		column_names.push_back(table_one.getColumnName(i));
		column_types.push_back(table_one.getColumnTypeAt(i));
	}
	table result("", column_names, column_types, one_primary_keys, table_one.getColumnWidths());
	
	//Find duplicates in table_two and blacklist their indices.
	for(int i = 0; i<one_num_entities; ++i)
	{
		entity_one = table_one.getEntityAt(i);
		for(int j = 0; j<two_num_entities;++j)
		{
			primary_keys_match = true;
			entity_two = table_two.getEntityAt(j);
			for(unsigned int k=0; k<one_primary_keys.size(); ++k)
			{
				one_key = one_primary_keys.at(k);
				two_key = same_columns[one_key];
				if(!(entity_one.getAttribute(one_key) == entity_two.getAttribute(two_key)))
				{
					primary_keys_match = false; //Atleast one key doesn't match
					break;
				}
			}
			if(primary_keys_match)
			{
				black_list_entities.push_back(j);
				break;
			}
		}
		result.addEntity(entity_one); //After looking for duplicate, add item
	}
	
	bool is_black_listed = false;
	//Now, if not blacklisted, format new entities like those of table_one.
	for(int i = 0; i<two_num_entities; ++i)
	{
		entity_two = table_two.getEntityAt(i);
		for(unsigned int j = 0; j<black_list_entities.size(); ++j)
		{
			if(i == black_list_entities.at(j))
			{
				is_black_listed = true;
				break;
			}
		}
		if(!is_black_listed)
		{
			entity formatted_entity;
			for(unsigned int j = 0; j<one_num_columns; ++j) //Column by column reformat
			{
				
				attribute copied_attr = entity_two.getAttribute(same_columns[j]);
				formatted_entity.addAttribute(copied_attr);
				
			}
			result.addEntity(formatted_entity);
		}
		is_black_listed = false;
	}
	return result;
}

table Database::setDifference(table table_one, table table_two){
	unsigned int one_num_columns = table_one.numOfColumns();
	unsigned int two_num_columns = table_two.numOfColumns();
	unsigned int one_key = 0;
	unsigned int two_key = 0;
	vector <unsigned int> one_primary_keys;
	vector <unsigned int> two_primary_keys;
	one_primary_keys = table_one.getPrimaryKeys();
	two_primary_keys = table_two.getPrimaryKeys();
	bool primary_keys_match = false;
	map<unsigned int, unsigned int> same_columns;
	//Check that two tables have same columns.
	if(one_num_columns != two_num_columns)
	{
		table non_difference_compatible;
		non_difference_compatible.error_code = ERR_TOO_MANY_COLUMNS;
		return non_difference_compatible;
	}	

	//Cycle through all column names, and map the same ones together. If not same, explode.
	for(unsigned int i = 0; i<one_num_columns; ++i)
	{
		string one_col_name = table_one.getColumnName(i);
		same_columns[i]=two_num_columns; //A number that is guaranteed not to be valid index
		for(unsigned int j = 0; j<two_num_columns; ++j)
		{
			string two_col_name = table_two.getColumnName(j);
			if(one_col_name == two_col_name)
			{
				same_columns[i]=j;
			}
		}
		if(same_columns[i]==two_num_columns) //A column did not match. Column mismatch.
		{
			table non_difference_compatible;
			non_difference_compatible.error_code = ERR_COLUMN_MISMATCH;
			return non_difference_compatible;			
		}
	}
	//Since column mismatch did not occur and num columns same- can check all indices safely
	for(unsigned int i = 0; i < one_primary_keys.size(); ++i)
	{
		one_key = one_primary_keys.at(i);
		for(unsigned int j = 0; j < two_primary_keys.size(); ++j)
		{
			two_key = two_primary_keys.at(j);
			if(same_columns[i] == two_key)
			{
				primary_keys_match = true;
			}
		}
		if(primary_keys_match)
		{
			primary_keys_match = false;
		}
		else //Tables don't share the same keys.
		{
			table non_difference_compatible;
			non_difference_compatible.error_code = ERR_PRIMARY_KEY_MISMATCH;
			return non_difference_compatible;			
		}
	}
	
	//Now, create new table which has what the other table doesn't
	int one_num_entities = table_one.getNumOfEntities();
	int two_num_entities = table_two.getNumOfEntities();
	vector <string> column_names;
	vector <unsigned int> column_types;
	entity entity_one;
	entity entity_two;
	for(unsigned int i = 0; i<one_num_columns;++i)
	{
		column_names.push_back(table_one.getColumnName(i));
		column_types.push_back(table_one.getColumnTypeAt(i));
	}
	table result("", column_names, column_types, one_primary_keys, table_one.getColumnWidths());
	
	primary_keys_match = true;
	bool duplicate_found = false;
	//Compare entities by primary key.
	for(int i = 0; i<one_num_entities; ++i)
	{
		entity entity_one = table_one.getEntityAt(i);
		for(int j = 0; j<two_num_entities;++j)
		{
			entity entity_two = table_two.getEntityAt(j);
			for(unsigned int k=0; k<one_primary_keys.size(); ++k)
			{
				one_key = one_primary_keys.at(k);
				two_key = same_columns[one_key];
				//If a primary key doesn't match, can't be duplicate. Go to next item
				if(!(entity_one.getAttribute(one_key) == entity_two.getAttribute(two_key)))
				{
					primary_keys_match = false;
					break;
				}
			}
			if(primary_keys_match)
			{
				duplicate_found = true;
				primary_keys_match = true;
				break;
			}
			else
			{
				primary_keys_match = true;
			}
		}
		if(!duplicate_found)
		{
			result.addEntity(entity_one);
		}
		duplicate_found = false;
	}
	return result;
}

//returns the number of tables being stored
int Database::getNumOfTables(){
	return table_list.size();
}

void Database::addQuery(table new_query){ //This kills a different bug.
	new_query.setAsQuery();
	for(unsigned int i = 0; i < table_list.size(); i++){
		if(table_list[i].getName() == new_query.getName()){
			//table_list.erase(table_list.begin() + i);
			table_list[i] = new_query;
			if( table_list[i]== new_query )
			{
				cout << "Good\n";
			}
			else
				cout << "Bad\n";
			return;
			//break;
		}
	}
	table_list.push_back(new_query);
}

void Database::removeAllQueries(){
	for(unsigned int i = 0; i < table_list.size(); i++){
		if(table_list[i].checkQuery()){
			table_list.erase(table_list.begin() + i);
		}
	}
}

void Database::addTable(table new_table){
	for(unsigned int i = 0; i < table_list.size(); i++){
		if(table_list[i].getName() == new_table.getName()){
			table_list[i] = new_table;
			return;
		}
	}
	table_list.push_back(new_table);
}

void Database::notifyFinish(){
	is_finished = true;
}

bool Database::isFinished()
{
	return is_finished;
}
