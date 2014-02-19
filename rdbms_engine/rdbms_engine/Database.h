#ifndef DATABASE_GUARD
#define DATABASE_GUARD

using namespace std;
#include "table.h"
#include "Condition.h"
#include "Parser.h"
#include <iomanip>

#include <map>
#define ERR_TOO_MANY_COLUMNS 0x20
#define ERR_PRIMARY_KEY_MISMATCH 0x21
#define ERR_COLUMN_MISMATCH 0x22

class Database
{
private:
	vector<table> table_list; //holds queries and tables
	bool is_finished;
public:

	Database();
	void execute(vector<string>& results, string command, Database& db);
	void createTable(string table_name, vector<string> attribute_names, vector<unsigned int> attr_types, vector<unsigned int> primary_key, vector<unsigned int> column_lengths);
	void dropTable(string table_name);
	static table select(Condition condition, table source_table);
	void deleteFromTable(string table_name, Condition condition);
	void insertIntoTable(string table_name, table source_table);
	void insertIntoTable(string table_name, vector<attribute> attr_list);
	void updateEntity(string table_name, vector<string> attr_names, vector<attribute> attr_literals, Condition condition);
	static table project(vector<string> attr_list, table source_table);
	static table rename(vector<string> new_column_names, table original_table);
	static table setUnion(table table_one, table table_two);
	static table setDifference(table table_one, table table_two);
	static table crossProduct(table table_one, table table_two);
	static table naturalJoin(table table_one, table table_two);
	table& findTable(string table_name);
	int getNumOfTables();
	int indexOfTable(string table_name);
	void addQuery(table new_query);
	void addTable(table new_table);
	void removeAllQueries();
	bool isFinished();
	void notifyFinish();
};
#endif
//maybe add some comments into the object classes
//update the style in attribute class
//change the class names to start with uppercase letter
//change the name of Database to DatabaseManager or DBManager
//make the relational alegbra functions static
//add error handling
	//union & difference: when the two tables are not union compatible