#include "attribute.h"


/*Basic attribute. Cannot get meaningful value*/

attribute::attribute()
{
	type = UNDEFINED;
	num_value = 0;
	str_value = "";
	str_length = 0;
}

attribute::attribute(string _value, int _length){
	str_value = _value;
	str_length = _length;
	num_value = 0;
	type = STRING;
}

attribute::attribute(int _value){
	num_value = _value;
	str_length = 0;
	str_value = "";
	type = INTEGER;
}

int attribute::getLength(){
	return str_length;
}

string attribute::get_string_value()
{
	if(type == INTEGER){
		return to_string(num_value);
	}
	return str_value;
}

int attribute::get_int_value()
{
	if(type == STRING){
		return -1;
	}

	return num_value;
}
