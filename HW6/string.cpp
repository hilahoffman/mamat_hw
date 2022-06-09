#include "string.h"
#include "stdio.h"
#include <cstring>
#include <iostream>

enum {ERROR=0, ZERO='0', NINE='9'};


String::String()
{
	length = 0;
	this->data = new char[length+1];
	strcpy(data,"");
}

String::String(const String &str)
{
	length = str.length;
	this->data = new char[length+1];
	strcpy(data ,str.data);
}


   String::String(const char *str){
	length = strlen(str);
	data = new char[length + 1];
	strcpy(data ,str);
}
	
	
String::~String(){
	delete[] data;
}


String& String::operator=(const String &rhs){
	if(this == &rhs) {
		return *this;
	}
	length = rhs.length;
	delete[] data; 
	data = new char[length + 1];
	strcpy(data, rhs.data);
	return *this;
}


String& String::operator=(const char *str) {
	delete[] data; 
	length = strlen(str);
	data = new char[length + 1];
	strcpy(data, str);
	return *this;
}


bool String::equals(const String &rhs) const {
	if(strcmp(this->data,rhs.data) != 0) { /*returns 0 if strs are identical*/
		return false;
	}
	return true;
}


bool String::equals(const char *rhs) const {
	if(strcmp(this->data, rhs) != 0) { /*returns 0 if strs are identical*/
		return false;
	}
	return true;
}



void String::split(const char *delimiters, String **output,
		           size_t *size) const {
	int cnt_words = 0; /*counts the splitted words*/
	char *dup= new char [length+1];
	strcpy(dup,data);
	char *word = strtok(dup,delimiters);
	while(word) {
		cnt_words++;
		word = strtok(NULL, delimiters);
	}
	*size = (size_t)cnt_words;
	if(output == NULL){ /*we only want to compute the size */
		return;
	}
	*output = new String[cnt_words]; /*array of strings*/
	strcpy(dup,data);
	word = strtok(dup,delimiters); 
	for(int i=0; i<cnt_words; i++) {
		(*output)[i] = String(word);
		word = strtok(NULL, delimiters);
	}
	delete[] dup;
}


int String::to_integer() const{
	if(this->data == NULL){
		return ERROR; /*edge case: cause we cant the behavior of atoi in
		case of NULL*/
	}
	for(size_t i=0; i < length; i++){
		if(data[i] > NINE || data[i] < ZERO) { /*check if number*/
			return ERROR; 
		}
	}			
	return atoi(data); /*turn into integer*/
}




String String::trim() const{
	/*find the left cursor*/
	char *data_dup=new char[length+1]; 
	strcpy(data_dup, data);
	int left = 0;
	while(data_dup[left] == ' ') {
		left++;
	}
		
	/*find the right cursor */
	int right= length-1;
	while(data_dup[right] == ' ') {
		right--;
	}
	char *str=new char[right-left+2];
	/*copying the str between left to right*/
	int len= right-left+1;
	for(int index=0 ; index < len ; index++){
		str[index] = data_dup[left];
		left++;
	}
	str[len] = '\0';
	/*creating the string*/
	String out(str); 
	delete[] str;
	delete[] data_dup;
	return out;
}
