#ifndef EXPRESSION_GUARD
#define EXPRESSION_GUARD
#include "database.h"

class Expression
{
private:
	table arg_one_table;
	table arg_two_table;
	string operation;
	Condition condition;
	vector<string> attribute_list;
public:
	Expression(string op, table t1, table t2);
	Expression(string op, table t1, Condition cond);
	Expression(string op, table t1, vector<string> attr_list);
	table evaluate();
};

#endif
