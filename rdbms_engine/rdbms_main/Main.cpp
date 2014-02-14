using namespace std;
#include <iostream>
#include "Database.h"

int main(){
	cout << "Hello World" << endl;
	attribute a("Hello World", 11);

	string name = "Some Test Table";

			vector<unsigned int> types;
			types.push_back(STRING);
			types.push_back(INTEGER);

			vector<string> names;
			names.push_back("Some String Attribute");
			names.push_back("Some Integer Attribute");

			vector<unsigned int> primary_key;
			primary_key.push_back(0);

			table test_table(name, names, types, primary_key);

			entity e1;
			e1.addStringAttribute("test value", 10);
			e1.addIntAttribute(50);
			test_table.addEntity(e1);

			entity e2;
			e2.addStringAttribute("another test value", 10);
			e2.addIntAttribute(33);
			test_table.addEntity(e2);

			Condition test_condition(test_table, "==");
			Condition test_condition_two(test_table, "==");

			test_condition.addFirstOperand("Some Integer Attribute");
			test_condition.addSecondOperand(attribute(50));

			test_condition_two.addFirstOperand("Some String Attribute");
			test_condition_two.addSecondOperand(attribute("another test value", 10));

	cout << test_condition.result(0) << endl;
	cout << test_condition_two.result(1) << endl;

	string temp;
	cin >> temp;
	return 0;
}