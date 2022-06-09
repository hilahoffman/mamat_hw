#include "ip.h"
#include "port.h"
#include "field.h"
#include "string.h"
#include "input.h"
#include <cstring>
#include <iostream>

#define FAIL -1

/**
 * @brief Tells if current paket suitable to field of rule.
 * @param argv one of the rules field.
 * @returns false if field invalid.
 */
int main (int argc, char** argv){
	
	if (check_args(argc , argv)!=0){
		return FAIL;
	}
	char *arg1 = argv[1]; 
	for (size_t i=0; i< strlen(arg1); i++){ /*turning ',' to ' ' so we
	can do trim*/
		if(arg1[i] == ',') {
			arg1[i] = ' ';
		}
	}
	
	String rule(arg1);
	String *output;
	size_t size;
	rule.split("=", &output, &size);
	String type = String(output[0].trim());
	if(type.equals(String("src-ip")) || type.equals(String("dst-ip"))) {
		Ip ip_rule = Ip(type);
		ip_rule.set_value(output[1].trim());
		parse_input(ip_rule);
	}
	else if(type.equals(String("src-port")) ||
			type.equals(String("dst-port"))) {
		Port port_rule = Port(type);
		port_rule.set_value(output[1].trim());
		parse_input(port_rule);
	}
	delete[] output;
	return 0; 
}
	
	
