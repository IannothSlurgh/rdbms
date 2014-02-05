#ifndef ATTRIBUTE_GUARD
#define ATTRIBUTE_GUARD

#define INT 0
#define STRING 1
#define UNDEFINED 3

#include "string"

using namespace std;

class attribute //Generally useless base class
{
public:
	unsigned int type;
	attribute();
	virtual string get_string_value();
	virtual int get_int_value();

};

class int_attribute : public attribute
{
	int value;
public:
	int_attribute();
	int_attribute( int _value );
	string get_string_value();
	int get_int_value();
};

class string_attribute : public attribute
{
	string value;
public:
	string_attribute();
	string_attribute( string _value );
	string get_string_value();
	int get_int_value();
};

#endif