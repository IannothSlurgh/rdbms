using namespace std;
#include "table.h"
#include "Condition.h"

#include <map>
#define ERR_TOO_MANY_COLUMNS 0x20
#define ERR_PRIMARY_KEY_MISMATCH 0x21
#define ERR_COLUMN_MISMATCH 0x22

class Database
{
private:
	vector<table> table_list; //holds queries and tables
public:

	Database();
	void execute(vector<string>& results, string command, string db_name);
	void createTable(string table_name, vector<string> attribute_names, vector<unsigned int> attr_types, vector<unsigned int> primary_key);
	void dropTable(string table_name);
	table select(Condition condition, table source_table);
	void deleteFromTable(string table_name, Condition condition);
	void insertIntoTable(string table_name, table source_table);
	void insertIntoTable(string table_name, vector<attribute> attr_list);
	void updateEntity(string table_name, vector<string> attr_names, vector<attribute> attr_literals, Condition condition);
	table project(vector<string> attr_list, table source_table);
	table rename(vector<string> new_column_names, table original_table);
	table setUnion(table table_one, table table_two);
	table setDifference(table table_one, table table_two);
	table crossProduct(table table_one, table table_two);
	table naturalJoin(table table_one, table table_two);
	table& findTable(string table_name);
	int getNumOfTables();
	int indexOfTable(string table_name);
};

//maybe relationals return table or the name of the query
//maybe store queries in same vector table
//might have to implement an expression class