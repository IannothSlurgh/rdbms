#pragma once
#include "Database.h"
#include "Expression.h"
#define FAIL 0
#define SUCCESS 1
#define LITERAL 10
#define RELATION_NAME 11
#define ANOTHER_CONDITION 12

class Parser
{
private:
	unsigned int location; //The point passed 0 where unparsed string begins
	string cmd_line; //The unparsed string that was input in the constructor
	Database & my_database; //The database from which the parser was constructed.
public:
	Parser( string input, Database & _my_database ); //Determine if command- which command- else query- else garbage
	unsigned int find( string token ); //Increment location 1 past the given token. Fail if not found.
	unsigned int parseQuery();
	unsigned int parseOpen();
	unsigned int parseClose();
	unsigned int parseWrite();
	unsigned int parseExit();
	unsigned int parseShow();
	unsigned int parseCreate();
	unsigned int parseDelete();
	unsigned int parseInsert();
	unsigned int parseUpdate();
	vector<string> parseAttributeList();
	string parseAttributeName();
	attribute parseAttributeLiteral();
	Condition parseCondition();
	table parseExpression();
	bool checkIfNext(string token); //checks to see in token starts at the current parse location, safer than find
	void parseAllWhitespace(); //advances the parser through whitespace
	string parseUntil( string end_token );//return the string in between location and a particular end token. If no such token, return ""
	void removeWhitespaceFrom(string& str); //remove whitespace from beginning and ending of str
};

