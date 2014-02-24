#ifndef TABLE_GUARD
#define TABLE_GUARD

#include "entity.h"
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

class table
{
private:
	vector <entity> entity_list;
	vector <string> column_names;
	vector <unsigned int> column_types;
	vector <unsigned int> primary_keys;
	vector <unsigned int> col_width;
	bool is_query;
	string name;
public:
	int error_code;

	table();
	table(string n, vector<string> cn, vector<unsigned int> ct, vector<unsigned int> pk, vector<unsigned int> cw);
	vector<unsigned int> getPrimaryKeys() const;
	void setAsQuery();
	int getAttributeColumn(string column_name);
	string getColumnName(int index);
	void removeEntity(int entity_index);
	entity getEntityAt(int index) const;
	unsigned int getColumnTypeAt(int column_index);
	entity getEntityWith(vector<attribute> primary_key);
	int entityExistsWith(vector<attribute> primary_attr);
	void renameColumn(string new_name, int index);
	string getName() const;
	vector<unsigned int> getColumnTypes() const;
	vector<unsigned int> getColumnWidths() const;
	vector<string> getColumnNames() const;
	vector<entity> getEntityList();
	void setEntityAt(int index, entity new_entity);
	int getNumOfEntities() const;
	void addEntity(entity new_entity);
	int numOfColumns();
	void changeName(string new_name);
	bool checkQuery() const;
	table & operator=(const table &t);
};
ostream& operator<<(ostream& os, table& t);
istream& operator>>(istream& is, table& t);
bool operator==(table& t1, table& t2);

#endif
