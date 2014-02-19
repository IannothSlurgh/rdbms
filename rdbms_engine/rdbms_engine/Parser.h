#ifndef PARSER_GUARD
#define PARSER_GUARD
#include "Database.h"
#include "Expression.h"
#include <queue>
#include <stack>
#include <iostream>
#include <sstream>
#include <fstream>
#define FAIL 0
#define SUCCESS 1
#define INT_WIDTH 15
#define LITERAL 10
#define RELATION_NAME 11
#define ANOTHER_CONDITION 12
class Database;
class Parser
{
private:
	unsigned int location; //The point passed 0 where unparsed string begins
	string cmd_line; //The unparsed string that was input in the constructor
	Database & my_database; //The database from which the parser was constructed.
	vector<string>& output;
public:
	Parser( string input, Database & _my_database, vector<string>& results); //Determine if command- which command- else query- else garbage
	unsigned int find( string token ); //Increment location 1 past the given token. Fail if not found.
	unsigned int parseQuery(); // Parsing the commands and creates a temporary table inside the database
	unsigned int parseOpen(); // Reads data from a file and inputs the data into table, and then into the database
	unsigned int parseClose(); // Saves data from the relation and puts it into a file
	unsigned int parseWrite(); // Creates a file to be written with a filename of "relationname".db
	unsigned int parseExit(); // Deletes all queries and closes the cmdline
	unsigned int parseShow(); // Outputs table to a vector of strings
	unsigned int parseCreate(); // Creates a table and inserts the table into the database
	unsigned int parseDelete(); // Deletes a table off the database
	unsigned int parseInsert(); // Inserts a table or entity into a table on the database
	unsigned int parseUpdate();	// Updates a table on the database with a new entity or attribute
	vector<string> parseAttributeList(); // Parses a list of attributes and returns a vector of attributes
	vector<attribute> parseLiteralList(); // Parses a list of literals and returns the list
	Condition parseCondition(); // Parses a condition and returns the said condition 
	table parseExpression(); // Parses the expression and returns a table
	bool checkIfNext(string token); //checks to see in token starts at the current parse location, safer than find
	void parseAllWhitespace(); //advances the parser through whitespace
	string parseUntil( string end_token );//return the string in between location and a particular end token. If no such token, return ""
	void removeWhitespaceFrom(string& str); //remove whitespace from beginning and ending of str
};
#endif
