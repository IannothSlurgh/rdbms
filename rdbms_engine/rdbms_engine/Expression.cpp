#include "Expression.h"


Expression::Expression(string op, table t1, table t2){
	operation = op;
	arg_one_table = t1;
	arg_two_table = t2;
}

Expression::Expression(string op, table t1, Condition cond){
	operation = op;
	arg_one_table = t1;
	condition = cond;
}

Expression::Expression(string op, table t1, vector<string> attr_list){
	operation = op;
	arg_one_table = t1;
	attribute_list = attr_list;
}

table Expression::evaluate(){
	if(operation == "select"){
		Database::select(condition, arg_one_table);
	}
	else if(operation == "project"){
		Database::project(attribute_list, arg_one_table);
	}
	else if(operation == "rename"){
		Database::rename(attribute_list, arg_one_table);
	}
	else if(operation == "JOIN"){
		Database::naturalJoin(arg_one_table, arg_two_table);
	}
	else if(operation == "+"){
		Database::setUnion(arg_one_table, arg_two_table);
	}
	else if(operation == "-"){
		Database::setDifference(arg_one_table, arg_two_table);
	}
	else if(operation == "*"){
		Database::crossProduct(arg_one_table, arg_two_table);
	}
	return table();
}
