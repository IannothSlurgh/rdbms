#include "Expression.h"


Expression::Expression(string op, table t1, table t2){
	operation = op;
	arg_one_table = t1;
	arg_two_table = t2;
}

Expression::Expression(string op, table t1, Condition cond) : condition(cond){
	operation = op;
	arg_one_table = t1;
}

Expression::Expression(string op, table t1, vector<string> attr_list){
	operation = op;
	arg_one_table = t1;
	attribute_list = attr_list;
}

table Expression::evaluate(){
	if(operation == "select"){
		return Database::select(condition, arg_one_table);
	}
	else if(operation == "project"){
		return Database::project(attribute_list, arg_one_table);
	}
	else if(operation == "rename"){
		return Database::rename(attribute_list, arg_one_table);
	}
	else if(operation == "JOIN"){
		return Database::naturalJoin(arg_one_table, arg_two_table);
	}
	else if(operation == "+"){
		return Database::setUnion(arg_one_table, arg_two_table);
	}
	else if(operation == "-"){
		return Database::setDifference(arg_one_table, arg_two_table);
	}
	else if(operation == "*"){
		return Database::crossProduct(arg_one_table, arg_two_table);
	}
	return table();
}
