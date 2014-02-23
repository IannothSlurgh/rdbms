using namespace std;
#include <iostream>
#include "Database.h"

int main(){
	Database db;
	init( db );
	bool appOperational = true;
	string choice = "";
	while( appOperational )
	{
		showMenu();
		getline( cin, choice );
		//if( choice == )
		//Series of else-ifs
		//exit command sets appOperational false.
		choice = "";
	}
}