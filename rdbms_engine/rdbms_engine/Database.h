using namespace std;
#include "table.h"
#include "Condition.h"

#define ERR_TOO_MANY_COLUMNS 0x20

class Database
{
private:
	vector<table> table_list; //will include both tables and queries
public:

	Database();
	void execute(vector<string>& results, string command, string db_name);
	void createTable(string table_name, vector<string> attribute_names, vector<unsigned int> attr_types, vector<unsigned int> primary_key);
	void dropTable(string table_name);
	void select(Condition condition, table t);
	void deleteFromTable(string table_name, Condition condition);
	void insertIntoTable(string table_name, table source_table);
	void insertIntoTable(string table_name, vector<attribute> attr_list);
	void updateEntity(string table_name, vector<string> attr_names, vector<attribute> attr_literals, Condition condition);
	table project(vector<attribute> attr_list, table source_table);
	table rename(vector<string> new_attr_names, table source_table);
	table setUnion(table table_one, table table_two);
	table difference(table table_one, table table_two);
	table crossProduct(table table_one, table table_two);
	table naturalJoin(table table_two, table table_one);
};

//maybe relationals return table or the name of the query
//maybe store queries in same vector table
//might have to implement an expression class