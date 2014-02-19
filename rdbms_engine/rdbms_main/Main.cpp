using namespace std;
#include <iostream>
#include "Database.h"

int main(){
	Database my_database;
	string input = "";
	
	/*Loop that goes on until user commands EXIT;*/
	while( ! my_database.isFinished() )
	{
		cout << "> ";
		vector <string> output;
		getline(cin , input);
		
		my_database.execute( output, input, my_database );
		//output the results of an execution
		for( int i = 0; i < output.size(); ++i )
		{
			cout << output.at( i ) << endl;
		}
		//Nuke the results, so new results can occur.
		output.clear();
	}
	return 0;
}