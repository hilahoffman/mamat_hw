#include "field.h"
#include "string.h"
#include <iostream>
#include <cstring>


Field::Field(String pattern) {
	this->pattern = pattern;
}

Field::~Field() {}

/* Returns true iff "packet" matches "this" */
bool Field::match(String packet) {
	String *output_fields; /*will contain the 4 words*/
	size_t size_of_fields; /*typecally there are 4 fields in packet*/
	packet.split(",", &output_fields, &size_of_fields); /*first we want to
	get the 4 fields seperately*/
	for(size_t i=0; i< size_of_fields ; i++)
	{
		size_t size_of;
		String *out;
		String word(output_fields[i]); /*pattern = number*/
		word.split("=", &out, &size_of);/*split according to =*/
		if(out[0].trim().equals(pattern)) {
			if (match_value(out[1].trim())) {
				delete[] output_fields;
				delete[] out; 
				return true;
			}
				
		}
		delete[] out;
	}
	delete[] output_fields;
	return false;
}
