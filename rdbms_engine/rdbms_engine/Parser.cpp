#include "Parser.h"

Condition parseCondition()
{
	
}

//have to include handling whitespace
table Parser::parseExpression()
{
	//get rid on any whitespace in front of the expresion
	parseAllWhitespace();
	
	table new_table;

	bool had_open_para = false;

	//if beginning starts with '('
	if(cmd_line.find("(", location) == location){
		location++;
		had_open_para = true; //determines whether there has been open paranthesis
		new_table = parseExpression(); //parsing whats inside the paranthesis
	}

	//if begins with select
	else if(cmd_line.find("select", location) == location){
		location += 6;
		parseAllWhitespace();
		Condition new_cond = parseCondition(); //find the condition
		table arg_table = parseExpression(); //either the relation name or another expression
		Expression new_expr("select", arg_table, new_cond);
		new_table = new_expr.evaluate(); //evaluate the expression
	}

	//begins with project
	else if(cmd_line.find("project", location) == location){
		location += 7;
		parseAllWhitespace();
		vector<string> attr_names = parseAttributeList();
		table arg_table = parseExpression();
		Expression new_expr("project", arg_table, attr_names);
		new_table = new_expr.evaluate();
	}

	//begins with rename
	else if(cmd_line.find("rename", location) == location){
		location += 6;
		parseAllWhitespace();
		vector<string> attr_names = parseAttributeList();
		table arg_table = parseExpression();
		Expression new_expr("rename", arg_table, attr_names);
		new_table = new_expr.evaluate();
	}
	
	//operation
	else{
		string table_name = "";
		//reads the first relation name
		while(&cmd_line[location] != "*" || &cmd_line[location] != "+" || &cmd_line[location] != ";" || &cmd_line[location] != "-" || &cmd_line[location] != "("  || &cmd_line[location] != ")"  || &cmd_line[location] != "J"){
			table_name += cmd_line[location];
			location++;
		}
		location -= 1; //backtrack to the token
		removeWhitespaceFrom(table_name);
		//case of the cross product
		if(&cmd_line[location] == "*"){
			location += 1;
			string second_table_name = "";
			//read in the second relation name
			while(&cmd_line[location] != ")" || &cmd_line[location] != ";" || &cmd_line[location] != "("){
				second_table_name += cmd_line[location];
				location++;
			}
			removeWhitespaceFrom(second_table_name);
			table second_table = my_database.findTable(second_table_name);
			//covers the case where it is the start of another expression
			if(&cmd_line[location] == "("){
				second_table = parseExpression();
			}
			Expression new_expr("*", my_database.findTable(table_name), second_table);
			new_table = new_expr.evaluate();
		}
		//case of the union
		else if(&cmd_line[location] == "+"){
			location += 1;
			string second_table_name = "";
			//read in the second relation name
			while(&cmd_line[location] != ")" || &cmd_line[location] != ";" || &cmd_line[location] != "("){
				second_table_name += cmd_line[location];
				location++;
			}
			removeWhitespaceFrom(second_table_name);
			table second_table = my_database.findTable(second_table_name);
			//covers the case where there is another expression as the second arguement
			if(&cmd_line[location] == "("){
				second_table = parseExpression();
			}
			Expression new_expr("+", my_database.findTable(table_name), second_table);
			new_table = new_expr.evaluate();
		}
		//case of difference
		else if(&cmd_line[location] == "-"){
			location += 1;
			string second_table_name = "";
			//read in the second relation name
			while(&cmd_line[location] != ")" || &cmd_line[location] != ";" || &cmd_line[location] != "("){
				second_table_name += cmd_line[location];
				location++;
			}
			removeWhitespaceFrom(second_table_name);
			table second_table = my_database.findTable(second_table_name);
			//covers the case where there is another expression as the second arguement
			if(&cmd_line[location] == "("){
				second_table = parseExpression();
			}
			Expression new_expr("-", my_database.findTable(table_name), second_table);
			new_table = new_expr.evaluate();
		}
		//case of natural join
		else if(checkIfNext("JOIN")){
			string second_table_name = "";
			//read in the second relation name
			while(&cmd_line[location] != ")" || &cmd_line[location] != ";" || &cmd_line[location] != "("){
				second_table_name += cmd_line[location];
				location++;
			}
			removeWhitespaceFrom(second_table_name);
			table second_table = my_database.findTable(second_table_name);
			//covers the case where there is another expression as the second arguement
			if(&cmd_line[location] == "("){
				second_table = parseExpression();
			}
			Expression new_expr("JOIN", my_database.findTable(table_name), second_table);
			new_table = new_expr.evaluate();
		}
		//case of another expression
		else if(&cmd_line[location] == "("){
			new_table = parseExpression();
		}
		//otherwise, the first relation name parsed in the only thing in this expression
		else{
			new_table = my_database.findTable(table_name);
		}
	}

	if(checkIfNext(")") || checkIfNext(";")){
		return new_table;
	}
	//this is used in case there are no paranthesis and it is only a relation name
	else if(had_open_para == false){
		return new_table;
	}

	return table();
}

unsigned int Parser::find( string token )
{
	unsigned int token_loc = cmd_line.find(token, location);
	if( token_loc == string::npos )
	{
		return FAIL;
	}
	location = token_loc + token.size();//Go to index after the found token.
	return SUCCESS;
}

Parser::Parser( string input, Database& _my_database )
{
	my_database = _my_database;
	cmd_line = input;
	if( find( "OPEN" ) )
	{
		parseOpen();
	}
	else if( find( "CLOSE" ) )
	{
		parseClose();
	}
	else if( find( "WRITE" ) )
	{
		parseWrite();
	}
	else if( find( "EXIT" ) )
	{
		parseExit();
	}
	else if( find( "SHOW" ) )
	{
		parseShow();
	}
	else if( find( "CREATE TABLE" ) )
	{
		parseCreate();
	}
	else if( find( "DELETE FROM" ) )
	{
		parseDelete();
	}
	else if( find( "INSERT INTO" ) )
	{
		parseInsert();
	}
	else if( find( "UPDATE" ) )
	{
		parseUpdate();
	}
	else if( find("<-") )
	{
		parseQuery();
	}
	else
	{
		//Die horrible death.
	}
}

string Parser::parseUntil( string end_token )
{
	unsigned int token_loc = cmd_line.find( end_token, location );
	if( token_loc == string::npos )
	{
		return "";
	}
	//Get a chunk that is between location and the found token.
	string chunk_to_be_parsed = cmd_line.substr( location, token_loc - location );
	location = token_loc;
	return chunk_to_be_parsed;
}

unsigned int Parser::parseQuery()
{
	location = 0;
	string table_name = parseUntil("<-");
	if(table_name != "")
	{
		find("<-");
		table result = parseExpression();
		if( result.error_code == 0 )
		{
			result.changeName( table_name );
			my_database.addQuery(result);
		}
		else
		{
			return FAIL;
		}
	}
	else
	{
		return FAIL;
	}
}

unsigned int Parser::parseCreate()
{

}

//safer, only looks at what is directly in front of it
bool Parser::checkIfNext(string token){
	for(int i = 0; i < token.size(); i++){
		if(token[i] != cmd_line[location + i]){
			return false;
		}
	}
	location += token.size();
	return true;
}

void Parser::parseAllWhitespace(){
	while(&cmd_line[0] == " "){ 
		location++;
	}
}

void Parser::removeWhitespaceFrom(string& str){
	int str_begin_index = str.find_first_not_of(' ');
	int str_end_index = str.find_last_not_of(' ');
	str.substr(str_begin_index, str_end_index);
}
