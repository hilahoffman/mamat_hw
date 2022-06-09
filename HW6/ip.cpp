#include "ip.h"
#include "field.h"
#include "string.h"
#include <iostream>
#include <cstring>

#define MIN_IP 0
#define MAX_IP 255

#define MIN_NUM_OF_BITS 0
#define MAX_NUM_OF_BITS 32

#define HIGHIEST_VALUE 0xFFFFFFFF

bool Ip::match_value(String value) const { 
	unsigned int ip_num = 0; 
	String *out_dot;
	size_t size_dot;

	value.split(".", &out_dot, &size_dot);/*spliting according to dot*/
	int multiplier=24;
	for(size_t i=0; i<4; i++){
		unsigned int decimal=(unsigned)out_dot[i].trim().to_integer();
		if(decimal < MIN_IP || decimal > MAX_IP) { /*in case not valid byte*/
			delete[] out_dot;
			return false;
		}
		ip_num += (decimal << multiplier);
		multiplier -= 8; 
	}
	delete[] out_dot;

	if(ip_num >= min_ip && ip_num <= max_ip)
		return true;
	return false;
}
	



bool Ip::set_value(String value) {
	/*for exampel data.value=3.3.64.8/14*/
	String *out_slesh;
	size_t size_slesh;
	value.split("/", &out_slesh, &size_slesh);/*out_slesh[1] contain
	the number after the slesh*/
	int num_of_bits= out_slesh[1].trim().to_integer();/*the number of bits
	we should take from the ip (from left)*/
	if(num_of_bits < MIN_NUM_OF_BITS || num_of_bits > MAX_NUM_OF_BITS) {
		delete[] out_slesh;
		return false; 
	}
	/*num_of_bits should be a sade of ip*/
	String *out_dot;
	size_t size_dot;

	out_slesh[0].split(".", &out_dot, &size_dot);/*spliting according to dot*/
	unsigned int sum=0;
	int multiplier=24;
	for(size_t i=0; i<4; i++){
		int decimal= out_dot[i].trim().to_integer(); /*for exampel decimal=3
		(the first byte in decimal)*/
		if(decimal < MIN_IP || decimal > MAX_IP) { /*in case not valid byte*/
			delete[] out_slesh;
			delete[] out_dot;
			return false;
		}
		sum += (decimal << multiplier);
		multiplier -= 8; 
	}
	delete[] out_slesh;
	delete[] out_dot;
	
	int num_of_first_bits= MAX_NUM_OF_BITS-num_of_bits;
	unsigned int mask;
	if(num_of_first_bits == MAX_NUM_OF_BITS)
		mask = HIGHIEST_VALUE;
	else mask = ((unsigned int) 1 << num_of_first_bits) - 1;

	min_ip = sum & (~mask);
	max_ip = sum | mask;
	return true;
}		
	
	
Ip::Ip(String pattern): Field(pattern) {}

Ip::~Ip() { }

