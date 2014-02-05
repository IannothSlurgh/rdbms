#include "attribute.h"

/*Basic attribute. Cannot get meaningful value*/

attribute::attribute()
{
	type = UNDEFINED;
}

string attribute::get_string_value()
{
	return "";
}

int attribute::get_int_value()
{
	return 0;
}

/*Int Attribute- Gives meaningful int value*/

int_attribute::int_attribute()
{
	type = INTEGER;
	value = 0;
}

int_attribute::int_attribute( int _value )
{
	type = INTEGER;
	value = _value;
}

string int_attribute::get_string_value()
{
	return "";
}

int int_attribute::get_int_value()
{
	return value;
}

/*string Attribute- Gives meaningful string value*/

string_attribute::string_attribute()
{
	type = STRING;
	value = "";
}

string_attribute::string_attribute( int _value )
{
	type = STRING;
	value = _value;
}

string string_attribute::get_string_value()
{
	return value;
}

int string_attribute::get_int_value()
{
	return 0;
}