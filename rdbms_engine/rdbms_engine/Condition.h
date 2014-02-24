#ifndef CONDITION_GUARD
#define CONDITION_GUARD
#include "table.h"
#include <string>

#define CONDITION 1
#define TYPE 2
#define ATTR 3
#define ERROR -1

#include <iostream>

class Condition
{
private:
	table data_table;
	string operation;
	int no_table;

	int operand_one_code; //determines whether the first operand is a condition, attribute, or type of attribute
	Condition* op_one_cond;
	string op_one_type;
	attribute op_one_attr;

	int operand_two_code;//determines whether the second operand is a condition, attribute, or type of attribute
	Condition* op_two_cond; 
	string op_two_type;
	attribute op_two_attr;

public:
	Condition();	
	Condition(string op);
	Condition(table t, string op);


	void addFirstOperand(Condition c);
	void addFirstOperand(string attribute_type);
	void addFirstOperand(attribute a);

	void addSecondOperand(Condition c);
	void addSecondOperand(string attribute_type);
	void addSecondOperand(attribute a);

	void addReferenceTable(table new_table);

	bool result(int row_num); //row_num is the location of an entity to test in the table
};

#endif