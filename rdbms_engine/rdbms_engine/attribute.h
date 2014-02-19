#ifndef ATTRIBUTE_GUARD
#define ATTRIBUTE_GUARD

#define INTEGER 0
#define STRING 1
#define UNDEFINED 3

#include "string"

using namespace std;

class attribute //Generally useless base class
{

public:
	unsigned int type;
	int num_value;
	string str_value;
	attribute();
	attribute(string _value);
	attribute(int _value);
	string get_string_value();
	int get_int_value();
	unsigned int getType();
	
};
bool operator==(attribute& a1, attribute& a2);

#endif