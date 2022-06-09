#include "port.h"
#include "field.h"
#include "string.h"
#include <iostream>
#include <cstring>

#define MIN_PORT 0
#define MAX_PORT 65535

bool Port::match_value(String value) const { 
	if(value.trim().to_integer() <= up &&
	   value.trim().to_integer() >= down) { /*check if value in range*/
		return true;
	}
	return false;
}
    
Port::Port(String pattern): Field(pattern) {}
    
Port::~Port() {}
    
bool Port::set_value(String val) {
	String *output; /*will contain the numbers before and after '-'*/
	size_t size; /*will contain number of splitted values*/
	val.split("-", &output, &size); /*split according to '-'*/
	int down_tmp = output[0].trim().to_integer();
	int up_tmp = output[1].trim().to_integer();
	delete[] output;
	/*if down or up values are not reasonable*/
	if(down_tmp > up_tmp || up_tmp < MIN_PORT || down_tmp < MIN_PORT ||
	   up_tmp > MAX_PORT || down_tmp > MAX_PORT) {
		return false;
	}
	down = down_tmp;
	up = up_tmp;
	return true;
}


