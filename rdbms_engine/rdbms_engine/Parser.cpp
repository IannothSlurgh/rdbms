
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
