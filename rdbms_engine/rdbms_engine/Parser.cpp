#include "Parser.h"

//returns the priority of token
unsigned int tokenValue(string token)
{
	if(token == "(")
	{
		return 6;
	}

	else if(token == ")")
	{
		return 6;
	}

	else if(token == "||")
	{
		return 4;
	}

	else if(token == "&&")
	{
		return 4;
	}

	else if(token == "!=")
	{
		return 2;
	}
	else if(token == "==")
	{
		return 2;
	}
	else if(token == ">=")
	{
		return 2;
	}
	else if(token == "<=")
	{
		return 2;
	}
	else if(token == ">")
	{
		return 2;
	}
	else if(token == "<")
	{
		return 2;
	}
	return 0;
}

//determines whether token_one has higher, lower, or equal priority
int compareTokens(string token_one, string token_two)
{
	return tokenValue(token_one) - tokenValue(token_two);
}

bool isNumeric(string str){
	for(unsigned int i = 0; i < str.length(); i++)
	{
		if(!isdigit(str[i]))
		{
			return false;
		}
	}
	return true;
}

Condition Parser::parseCondition()
{
	stack<string> token_queue;
	stack<Condition> cond_queue;
	stack<string> arg_queue;

	if(checkIfNext("("))
	{
		token_queue.push("(");
	}

	while(!token_queue.empty()){
		string arg = "";
		//add characters to arg until a token is found
		while(cmd_line[location] != '(' && cmd_line[location] != ')' && cmd_line[location] != '!' && cmd_line[location] != '=' && cmd_line[location] != '>' && cmd_line[location] != '<' && cmd_line[location] != '&' && cmd_line[location] != '|' && cmd_line[location] != ';'){
			arg += cmd_line[location];
			location++;
		}

		removeWhitespaceFrom(arg);
		if(arg != "")
		{
			arg_queue.push(arg);
		}
		

		string current_token = "";
		string prev_token = token_queue.top();

		if(checkIfNext("("))
		{
			token_queue.push("(");
		}
		else if(checkIfNext("||"))
		{
			if(compareTokens(prev_token, "||") > 0)
			{
				//do nothing
			}
			else if(compareTokens(prev_token, "||") < 0)
			{
				
				if(prev_token == "&&")
				{
					Condition new_cond(prev_token);
					new_cond.addSecondOperand(&cond_queue.top());
					cond_queue.pop();
					new_cond.addFirstOperand(&cond_queue.top());
					cond_queue.pop();
					cond_queue.push(new_cond);
				}
				//must be an op
				else
				{
					token_queue.pop(); //remove prev_token
					Condition new_cond(prev_token);
					string arg_two = arg_queue.top();
					arg_queue.pop();
					string arg_one = arg_queue.top();
					arg_queue.pop();

					if(isNumeric(arg_two))
					{
						new_cond.addSecondOperand(attribute(atoi(arg_two.c_str())));
					}
					else if(arg_two[0] == '\"' && arg_two[arg_two.length() - 1] == '\"')
					{
						arg_two.erase(0);
						arg_two.erase(arg_two.end());
						new_cond.addSecondOperand(attribute(arg_two));
					}
					else
					{
						new_cond.addSecondOperand(arg_two);
					}

					if(isNumeric(arg_one))
					{
						new_cond.addFirstOperand(attribute(atoi(arg_one.c_str())));
					}
					else if(arg_one[0] == '\"' && arg_one[arg_one.length() - 1] == '\"')
					{
						arg_two.erase(0);
						arg_two.erase(arg_one.end());
						new_cond.addFirstOperand(attribute(arg_one));
					}
					else
					{
						new_cond.addFirstOperand(arg_one);
					}

					cond_queue.push(new_cond);
				}
				
			}
			else
			{
				Condition new_cond(prev_token);
				new_cond.addSecondOperand(&cond_queue.top());
				cond_queue.pop();
				new_cond.addFirstOperand(&cond_queue.top());
				cond_queue.pop();
				cond_queue.push(new_cond);
			}
			token_queue.push("||");
		}
		else if(checkIfNext("&&"))
		{
			if(compareTokens(prev_token, "&&") > 0){
				//do nothing
			}
			else if(compareTokens(prev_token, "&&") < 0)
			{
				//must be an op
				token_queue.pop(); //remove prev_token
				Condition new_cond(prev_token);

				string arg_two = arg_queue.top();
				arg_queue.pop();
				string arg_one = arg_queue.top();
				arg_queue.pop();

				if(isNumeric(arg_two))
				{
					new_cond.addSecondOperand(attribute(atoi(arg_two.c_str())));
				}
				else if(arg_two[0] == '\"' && arg_two[arg_two.length() - 1] == '\"')
				{
					arg_two.erase(0);
					arg_two.erase(arg_two.end());
					new_cond.addSecondOperand(attribute(arg_two));
				}
				else
				{
					new_cond.addSecondOperand(arg_two);
				}

				if(isNumeric(arg_one))
				{
					new_cond.addFirstOperand(attribute(atoi(arg_one.c_str())));
				}
				else if(arg_one[0] == '\"' && arg_one[arg_one.length() - 1] == '\"')
				{
					arg_two.erase(0);
					arg_two.erase(arg_one.end());
					new_cond.addFirstOperand(attribute(arg_one));
				}
				else
				{
					new_cond.addFirstOperand(arg_one);
				}
				cond_queue.push(new_cond);
			}
			else
			{
				Condition new_cond(prev_token);
				new_cond.addSecondOperand(&cond_queue.top());
				cond_queue.pop();
				new_cond.addFirstOperand(&cond_queue.top());
				cond_queue.pop();
				cond_queue.push(new_cond);
			}
			token_queue.push("&&");
		}
		else if(checkIfNext("=="))
		{
			token_queue.push("==");
		}
		else if(checkIfNext("!="))
		{
			token_queue.push("!=");
		}
		else if(checkIfNext(">="))
		{
			token_queue.push(">=");
		}
		else if(checkIfNext("<="))
		{
			token_queue.push("<=");
		}
		else if(checkIfNext(">"))
		{
			token_queue.push(">");
		}
		else if(checkIfNext("<"))
		{
			token_queue.push("<");
		}
		else if(checkIfNext(")"))
		{
			while(prev_token != "(")
			{
				if(prev_token != "&&" && prev_token != "||")
				{
					Condition new_cond(prev_token);

					string arg_two = arg_queue.top();
					arg_queue.pop();
					string arg_one = arg_queue.top();
					arg_queue.pop();

					if(isNumeric(arg_two))
					{
						new_cond.addSecondOperand(attribute(atoi(arg_two.c_str())));
					}
					else if(arg_two[0] == '\"' && arg_two[arg_two.length() - 1] == '\"')
					{
						arg_two.erase(0);
						arg_two.erase(arg_two.end());
						new_cond.addSecondOperand(attribute(arg_two));
					}
					else
					{
						new_cond.addSecondOperand(arg_two);
					}

					if(isNumeric(arg_one))
					{
						new_cond.addFirstOperand(attribute(atoi(arg_one.c_str())));
					}
					else if(arg_one[0] == '\"' && arg_one[arg_one.length() - 1] == '\"')
					{
						arg_two.erase(0);
						arg_two.erase(arg_one.end());
						new_cond.addFirstOperand(attribute(arg_one));
					}
					else
					{
						new_cond.addFirstOperand(arg_one);
					}
					cond_queue.push(new_cond);
				}
				else
				{
					Condition new_cond(prev_token);
					new_cond.addSecondOperand(&cond_queue.top());
					cond_queue.pop();
					new_cond.addFirstOperand(&cond_queue.top());
					cond_queue.pop();
					cond_queue.push(new_cond);

				}
				token_queue.pop();
				
				prev_token = token_queue.top();
			}
			token_queue.pop();
			if(token_queue.size() == 0)
			{
				Condition c = cond_queue.top();
				return c;
			}
		}
		else if(checkIfNext(";"))
		{
			while(!token_queue.empty())
			{
				if(prev_token != "&&" && prev_token != "||")
				{
					Condition new_cond(prev_token);

					string arg_two = arg_queue.top();
					arg_queue.pop();
					string arg_one = arg_queue.top();
					arg_queue.pop();

					if(isNumeric(arg_two))
					{
						new_cond.addSecondOperand(attribute(atoi(arg_two.c_str())));
					}
					else if(arg_two[0] == '\"' && arg_two[arg_two.length() - 1] == '\"')
					{
						arg_two.erase(0);
						arg_two.erase(arg_two.end());
						new_cond.addSecondOperand(attribute(arg_two));
					}
					else
					{
						new_cond.addSecondOperand(arg_two);
					}

					if(isNumeric(arg_one))
					{
						new_cond.addFirstOperand(attribute(atoi(arg_one.c_str())));
					}
					else if(arg_one[0] == '\"' && arg_one[arg_one.length() - 1] == '\"')
					{
						arg_two.erase(0);
						arg_two.erase(arg_one.end());
						new_cond.addFirstOperand(attribute(arg_one));
					}
					else
					{
						new_cond.addFirstOperand(arg_one);
					}
					cond_queue.push(new_cond);
				}
				
				else
				{
					Condition new_cond(prev_token);
					new_cond.addSecondOperand(&cond_queue.top());
					cond_queue.pop();
					new_cond.addFirstOperand(&cond_queue.top());
					cond_queue.pop();
					cond_queue.push(new_cond);
				}
			}
		}
	}
	//at this point, there should only be one condition
	return cond_queue.top();
}

//have to include handling whitespace
table Parser::parseExpression()
{
	//get rid on any whitespace in front of the expresion
	parseAllWhitespace();
	
	table new_table;

	bool had_open_para = false;

	//if beginning starts with '('
	if(checkIfNext("(")){
		had_open_para = true; //determines whether there has been open paranthesis
		new_table = parseExpression(); //parsing whats inside the paranthesis
	}

	//if begins with select
	else if(cmd_line.find("select", location) == location){
		location += 6;
		parseAllWhitespace();
		Condition new_cond = parseCondition(); //find the condition
		table arg_table = parseExpression(); //either the relation name or another expression
		new_cond.addReferenceTable(arg_table);
		Expression new_expr("select", arg_table, new_cond);
		new_table = new_expr.evaluate(); //evaluate the expression
		cout << new_table << endl;
		if(cmd_line[location] == ';')
		{
			return new_table;
		}
	}

	//begins with project
	else if(checkIfNext("project")){
		parseAllWhitespace();
		vector<string> attr_names = parseAttributeList();
		parseAllWhitespace();
		table arg_table = parseExpression();
		Expression new_expr("project", arg_table, attr_names);
		new_table = new_expr.evaluate();
		if(cmd_line[location] == ';')
		{
			return new_table;
		}
	}

	//begins with rename
	else if(cmd_line.find("rename", location) == location){
		location += 6;
		parseAllWhitespace();
		vector<string> attr_names = parseAttributeList();
		table arg_table = parseExpression();
		Expression new_expr("rename", arg_table, attr_names);
		new_table = new_expr.evaluate();
		if(cmd_line[location] == ';')
		{
			return new_table;
		}
	}
	else if(checkIfNext(")") || checkIfNext(";")){
		return new_table;
	}
	
	//operation
	else{
		string table_name = "";
		//reads the first relation name
		while(cmd_line[location] != '*' && cmd_line[location] != '+' && cmd_line[location] != ';' && cmd_line[location] != '-' && cmd_line[location] != '('  && cmd_line[location] != ')'  && cmd_line[location] != 'J'){
			table_name += cmd_line[location];
			location++;
		}
		
		removeWhitespaceFrom(table_name);
		//case of the cross product
		if(cmd_line[location] == '*'){
			location += 1;
			string second_table_name = "";
			//read in the second relation name
			while(cmd_line[location] != ')' && cmd_line[location] != ';' && cmd_line[location] != '('){
				second_table_name += cmd_line[location];
				location++;
			}
			removeWhitespaceFrom(second_table_name);
			table second_table = my_database.findTable(second_table_name);
			//covers the case where it is the start of another expression
			if(cmd_line[location] == '('){
				second_table = parseExpression();
			}
			Expression new_expr("*", my_database.findTable(table_name), second_table);
			new_table = new_expr.evaluate();
		}
		//case of the union
		else if(cmd_line[location] == '+'){
			location += 1;
			string second_table_name = "";
			//read in the second relation name
			while(cmd_line[location] != ')' && cmd_line[location] != ';' && cmd_line[location] != '('){
				second_table_name += cmd_line[location];
				location++;
			}
			removeWhitespaceFrom(second_table_name);
			table second_table = my_database.findTable(second_table_name);
			//covers the case where there is another expression as the second arguement
			if(cmd_line[location] == '('){
				second_table = parseExpression();
			}
			Expression new_expr("+", my_database.findTable(table_name), second_table);
			new_table = new_expr.evaluate();
		}
		//case of difference
		else if(cmd_line[location] == '-'){
			location += 1;
			string second_table_name = "";
			//read in the second relation name
			while(cmd_line[location] != ')' && cmd_line[location] != ';' && cmd_line[location] != '('){
				second_table_name += cmd_line[location];
				location++;
			}
			removeWhitespaceFrom(second_table_name);
			table second_table = my_database.findTable(second_table_name);
			//covers the case where there is another expression as the second arguement
			if(cmd_line[location] == '('){
				second_table = parseExpression();
			}
			Expression new_expr("-", my_database.findTable(table_name), second_table);
			new_table = new_expr.evaluate();
		}
		//case of natural join
		else if(checkIfNext("JOIN")){
			string second_table_name = "";
			//read in the second relation name
			while(cmd_line[location] != ')' && cmd_line[location] != ';' && cmd_line[location] != '('){
				second_table_name += cmd_line[location];
				location++;
			}
			removeWhitespaceFrom(second_table_name);
			table second_table = my_database.findTable(second_table_name);
			//covers the case where there is another expression as the second arguement
			if(cmd_line[location] == '('){
				second_table = parseExpression();
			}
			Expression new_expr("JOIN", my_database.findTable(table_name), second_table);
			new_table = new_expr.evaluate();
		}
		//case of another expression
		else if(cmd_line[location] == '('){
			location += 1;
			new_table = parseExpression();
		}
		//otherwise, the first relation name parsed in the only thing in this expression
		else{
			new_table = my_database.findTable(table_name);
			if(checkIfNext(";"))
			{
				location -= 1;
				return new_table;
			}
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

Parser::Parser( string input, Database& _my_database, vector<string>& results )
	:my_database(_my_database), output(results)
{
	location = 0;
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
	else if( find( "EXIT" ))
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
		results.push_back("Error: Could not find command.");
	}
	results.push_back("");
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
	location = token_loc + end_token.size();
	return chunk_to_be_parsed;
}

unsigned int Parser::parseQuery()
{
	location = 0;
	string table_name = parseUntil("<-");
	removeWhitespaceFrom(table_name);
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
	return SUCCESS;
}

//safer, only looks at what is directly in front of it
bool Parser::checkIfNext(string token){
	for(unsigned int i = 0; i < token.size(); i++){
		if(token[i] != cmd_line[location + i]){
			return false;
		}
	}
	location += token.size();
	return true;
}

void Parser::parseAllWhitespace(){
	while(cmd_line[location] == ' '){ 
		location++;
	}
}

void Parser::removeWhitespaceFrom(string& str){
	for(int i = 0; i < str.size(); i++)
	{
		if(str[i] == ' ')
		{
			str.erase(str.begin() + i);
		}
		else
		{
			break;
		}
	}

	for(int i = str.size() - 1; i > 0; i--)
	{
		if(str[i] == ' ')
		{
			str.erase(str.begin() + i);
		}
		else
		{
			break;
		}
	}
}

unsigned int Parser::parseOpen()
{
	string file_name = parseUntil( ";" );
	removeWhitespaceFrom( file_name );
	file_name += ".db";
	ifstream input(file_name );
	table to_be_added;
	if( input.good() )
	{
		input >> to_be_added;
		if( !input.fail() && !input.bad() )
		{
			my_database.addTable( to_be_added );
			return SUCCESS;
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

unsigned int Parser::parseInsert()
{
	string table_name = parseUntil( "VALUES FROM" );
	removeWhitespaceFrom( table_name );
	/*Check validity of table*/
	table & my_table = my_database.findTable( table_name );
	if( my_table.getName() == "" )
	{
		return FAIL;
	}
	else
	{
		if( find( "RELATION" ) )
		{
			table data_to_add = parseExpression();
			if( data_to_add.error_code == 0 )
			{
				my_database.insertIntoTable( table_name, data_to_add );
				return SUCCESS;
			}
		}
		else
		{
			vector <attribute> attribute_list;
			attribute_list = parseLiteralList();
			if( attribute_list.size() != 0 ) //If size == 0, parseLiteralList failed
			{
				my_database.insertIntoTable( table_name, attribute_list );
				return SUCCESS;
			}
		}
	}
	return FAIL;
}

unsigned int Parser::parseDelete()
{
	string table_name = parseUntil( "WHERE" );
	removeWhitespaceFrom( table_name );
	/*Get table to verify that table_name is valid*/
	table & my_table = my_database.findTable( table_name );
	if( my_table.getName() == "" ) //Not a dummy.
	{
		return FAIL;
	}
	else
	{
		/*Heavy lifting done by parse condition*/
		Condition c = parseCondition();
		c.addReferenceTable( my_table );
		my_database.deleteFromTable( table_name, c );
		return SUCCESS;
	}		
}

unsigned int Parser::parseCreate() //Get primary keys, call my_database.create
{
	string table_name = parseUntil( "(" );
	removeWhitespaceFrom( table_name );
	vector<unsigned int> column_types;
	vector<string> column_names;
	vector<unsigned int> primary_keys;
	vector<unsigned int> column_lengths;
	if( table_name == "" )
	{
		return FAIL;
	}
	else
	{
		string all_typed_attributes = parseUntil( "PRIMARY KEY" );
		removeWhitespaceFrom( all_typed_attributes );
		unsigned int comma_spot = all_typed_attributes.find( ",", 0 ); //Comma spot also is last close )
		while( comma_spot != string::npos )//While a delimiting comma is found or last item is followed by )
		{
			string typed_attribute = all_typed_attributes.substr( 0, comma_spot ); //Get typed attribute string
			/*Remove the found attribute*/
			all_typed_attributes = all_typed_attributes.substr( typed_attribute.length() + 1, all_typed_attributes.length() - typed_attribute.length() );
			unsigned int varchar = typed_attribute.find( "VARCHAR", 0 );
			unsigned int integer = typed_attribute.find( "INTEGER", 0 );
			string column_name = "";
			if( integer != string::npos )
			{
				column_types.push_back( INTEGER );
				string column_name = typed_attribute.substr( 0, integer );
				removeWhitespaceFrom(column_name);
				column_names.push_back( column_name );
				column_lengths.push_back( INT_WIDTH );
			}
			else if( varchar != string::npos )
			{
				column_name = typed_attribute.substr( 0, varchar );
				removeWhitespaceFrom(column_name);
				unsigned int open = typed_attribute.find( "(", 0 );
				unsigned int close = typed_attribute.find( ")", 0 );
				if( open != string::npos && close != string::npos ) //Both parenthesis found
				{
					if( ( close > open ) && ( open > varchar ) && ( close > varchar ) ) //Order is correct
					{
						string length = typed_attribute.substr( open + 1, close - open - 1 );
						unsigned int length_as_int = atoi( length.c_str() );
						if( length_as_int == 0 )
						{
							return FAIL;
						}
						column_lengths.push_back( length_as_int );
						column_names.push_back( column_name );
						column_types.push_back( STRING );
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
			else
			{
				return FAIL;
			}
			comma_spot = all_typed_attributes.find("," ,0); //Find next non-last item as indicated by comma.
			if( comma_spot == string::npos )
			{
				comma_spot = all_typed_attributes.find(  ")",0 );
			}
		}
		/*Check for duplication in column names*/
		for( int i = 0; i < column_names.size(); ++i )
		{
			string column_name = column_names.at( i );
			for( int j = 0; j < column_names.size(); ++j )
			{
				if( ( i != j ) && ( column_name == column_names.at( j ) ) )
				{
					return FAIL;
				}
			}
		}
		vector <string> primary_key_names;
		primary_key_names = parseAttributeList();
		vector <unsigned int> primary_keys;
		/*Find indices of primary keys and load them into vector*/
		for( int i = 0; i < primary_key_names.size(); ++i )
		{
			string primary_key_name = primary_key_names.at( i );
			for( int j = 0; j < column_names.size(); ++j )
			{
				if( ( primary_key_name == column_names.at( j ) ) )
				{
					primary_keys.push_back( j );
				}
			}
		}
		/*No primary keys leads to failure*/
		if( primary_keys.size() == 0 )
		{
			return FAIL;
		}
		else
		{
			/*Finish*/
			my_database.createTable( table_name, column_names, column_types, primary_keys, column_lengths );
			return SUCCESS;
		}
	}
}

unsigned int Parser::parseShow()
{
	table data_table = parseExpression();
	if( data_table.getName() == "" )
	{
		return FAIL;
	}
	else
	{	
		vector<unsigned int> col_w = data_table.getColumnWidths();
		vector<string> col_name = data_table.getColumnNames();
		vector<entity> entity_list = data_table.getEntityList();
		string temp;
		for(int i = 0; i < col_name.size(); i++)
		{
			temp += (col_name[i] + " ");
		}

		output.push_back(temp);
		for(int i = 0; i < entity_list.size(); i++)
		{
			temp = "";
			for(int j = 0; j < entity_list[i].getNumOfAttributes(); j++)
			{
				temp += (entity_list[i].getAttribute(j).get_string_value() + " ");
			}
			output.push_back(temp);
		}
	}
	return SUCCESS;
}
unsigned int Parser::parseClose() // Write the table into the filename.db
{
	string table_name = parseUntil(";");
	removeWhitespaceFrom(table_name);
	table table_to_write = my_database.findTable(table_name);

	string file_name = table_name + ".db";
	ofstream table_file(file_name);
	if(table_file.is_open())
	{
		table_file << table_to_write;
		table_file.close();
	}
	else
	{
		return FAIL;
	}
	return SUCCESS;
}

unsigned int Parser::parseWrite() // Create a file with the table's name.db
{
	string table_name = parseUntil(";");
	removeWhitespaceFrom(table_name);
	table table_to_write = my_database.findTable(table_name);

	string file_name = table_name + ".db";
	ofstream table_file(file_name);

	if(table_file.is_open())
	{
		table_file.close();
	}
	else
	{
		return FAIL;
	}
	return SUCCESS;
}

unsigned int Parser::parseExit()
{
	if(find(";") == SUCCESS)
	{
		my_database.removeAllQueries();
		my_database.notifyFinish();
		return SUCCESS;
	}
	else
	{
		return FAIL;
	}
}

vector<string> Parser::parseAttributeList()
{
	find("(");
	string to_parse = parseUntil(")");
	istringstream iss(to_parse);
	string token;
	vector<string> attribute_list;
	while(getline(iss, token, ','))
	{
		removeWhitespaceFrom(token);
		attribute_list.push_back(token);
	}
	parseAllWhitespace();
	return attribute_list;
}

vector<attribute> Parser::parseLiteralList()
{
	find("(");
	string to_parse = parseUntil(")");
	istringstream iss(to_parse);
	string token;
	vector<string> literal_list;
	while(getline(iss, token, ','))
	{
		removeWhitespaceFrom(token);
		literal_list.push_back(token);
	}
	vector<attribute> attribute_list;
	for(vector<string>::iterator it = literal_list.begin(); it != literal_list.end(); ++it)  
	{
		string temp_parse = *it;
		if('\"' == temp_parse[0])
		{
			temp_parse.erase(temp_parse.begin());
			temp_parse.erase(temp_parse.end() - 1);
			attribute_list.push_back(attribute(temp_parse));
		}
		else
		{
			int parsed_int = atoi(temp_parse.c_str());
			attribute_list.push_back(attribute(parsed_int));
		}
	}

	return attribute_list;
}

unsigned int Parser::parseUpdate()
{
	string table_name = parseUntil("SET");
	string attribute_and_literal = parseUntil("WHERE");
	
	Condition cond = parseCondition();

	istringstream iss(attribute_and_literal);
	vector<string> to_parse;
	int i = 0;
	while(iss.good())
	{
		iss >> to_parse[i];
		i++;
	}
	vector<string> attribute_list;
	vector<attribute> attribute_lit;
	attribute_list.push_back(to_parse[0]);
	attribute_lit.push_back(attribute(to_parse[2]));

	my_database.updateEntity(table_name, attribute_list, attribute_lit, cond);
	return SUCCESS;
}