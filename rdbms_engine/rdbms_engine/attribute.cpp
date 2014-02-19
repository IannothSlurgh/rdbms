#include "attribute.h"


/*Basic attribute. Cannot get meaningful value*/

attribute::attribute()
{
	type = UNDEFINED;
	num_value = 0;
	str_value = "";
}

attribute::attribute(string _value){
	str_value = _value;
	num_value = 0;
	type = STRING;
}

attribute::attribute(int _value){
	num_value = _value;
	str_value = "";
	type = INTEGER;
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

unsigned int attribute::getType(){
	return type;
}

bool operator==(attribute& a1, attribute& a2){
	if(a1.getType() != a2.getType()){
		return false;
	}
	if(a1.getType() == STRING){
		return ((a1.get_string_value().compare(a2.get_string_value())) == 0);
	}
	return a1.get_int_value() == a2.get_int_value();
}
