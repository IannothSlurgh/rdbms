
#define FAIL 0
#define SUCCESS 1
#define INT_WIDTH 15

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
	Condition parseCondition();
	table parseExpression();
	bool checkIfNext(string token); //checks to see in token starts at the current parse location, safer than find
	void parseAllWhitespace(); //advances the parser through whitespace
	string parseUntil( string end_token );//return the string in between location and a particular end token. If no such token, return ""
	void removeWhitespaceFrom(string& str); //remove whitespace from beginning and ending of str
};