
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
		while(&cmd_line[location] != "*" || &cmd_line[location] != "+" || &cmd_line[location] != ";" || &cmd_line[location] != "-" || &cmd_line[location] != "("  || &cmd_line[location] != ")"  || !checkIfNext("JOIN")){
			table_name += cmd_line[location];
			location++;
		}
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

Parser::Parser( string input, Database & _my_database )
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
			my_database.addQuery( result );
			return ( result.error_code == SUCCESS ) //Return SUCCESS if SUCCESS, else FAIL
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

unsigned int Parser::parseOpen()
{
	string file_name = parseUntil( ";" );
	removeWhiteSpaceFrom( file_name );
	file_name += ".db";
	ifstream input( file_name );
	table to_be_added;
	if( file_name.good() )
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
	/*Check validity of table*/
	table & my_table = my_database.findTable( table_name );
	if( myTable.getName() == "" )
	{
		return FAIL;
	}
	else
	{
		if( find( "VALUES FROM" ) )
		{
			vector <attribute> attribute_list;
			attribute_list = parseLiteralList();
			if( attribute_list.size() != 0 ) //If size == 0, parseLiteralList failed
			{
				my_database.insertInto( table_name, attribute_list )
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
}

unsigned int Parser::parseDelete()
{
	string table_name = parseUntil( "WHERE" );
	/*Get table to verify that table_name is valid*/
	table & my_table = my_database.findTable( table_name );
	if( my_table.getName() == "" ) //Not a dummy.
	{
		return FAIL;
	}
	else
	{
		find( "WHERE" );
		/*Heavy lifting done by parse condition*/
		Condition c = parseCondition();
		c.addTableReference( my_table );
		my_database.deleteFrom( table_name, c );
		return SUCCESS;
	}		
}

unsigned int Parser::parseCreate() //Get primary keys, call my_database.create
{
	string table_name = parseUntil( "(" );
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
		if( find( "(" ) )
		{
			string all_typed_attributes = parseUntil( "PRIMARY KEY" );
			removeWhitespaceFrom( all_typed_attributes );
			unsigned int comma_spot = all_typed_attributes.find( 0, "," ); //Comma spot also is last close )
			while( comma_spot != string::npos )//While a delimiting comma is found or last item is followed by )
			{
				string typed_attribute = all_typed_attributes.substr( 0, comma_spot ); //Get typed attribute string
				/*Remove the found attribute*/
				all_typed_attributes = all_typed_attributes.substr( typed_attribute.length(), all_typed_attributes.length() - typed_attribute.length() );
				unsigned int varchar = typed_attribute.find( "VARCHAR", 0 );
				unsigned int integer = typed_attribute.find( "INTEGER", 0 );
				string column_name = "";
				if( integer != string::npos )
				{
					column_types.push_back( INTEGER );
					column_names.push_back( typed_attribute.substr( 0, varchar ) );
					column_lengths.push_back( INT_WIDTH );
				}
				else if( varchar != string::npos )
				{
					column_name = typed_attribute.substr( 0, integer );
					unsigned int open = typed_attribute.find( "(", 0 );
					unsigned int close = typed_attribute.find( ")", 0 );
					if( open != string::npos && close != string::npos ) //Both parenthesis found
					{
						if( ( close > open ) && ( open > varchar ) && ( close > varchar ) ) //Order is correct
						{
							string length = typed_attribute.substr( open, close - open );
							unsigned int length_as_int = atoi( length );
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
				comma_spot = all_typed_attributes.find( 0, "," ); //Find next non-last item as indicated by comma.
				if( comma_spot == string::npos )
				{
					comma_spot = all_typed_attributes.find( 0, ")" );
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
			find( "PRIMARY KEY" );
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
				my_database.createTable( column_names, column_types, primary_keys, column_lengths );
				return SUCCESS;
			}
		}
		else
		{
			return FAIL;
		}
	}
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

