#ifndef IP_H
#define IP_H

#include "string.h"
#include "field.h"

class Ip: public Field {
	unsigned int min_ip; /*min valid ip*/
	unsigned int max_ip; /*max valid ip*/
protected:
	/**
	   @param A string with the ip to check
     * @brief Returns true iff "value" matches the value of this 
     	(e.g., if 1.1.1.1
      	 matches 1.1.*.*)
       @return boolean 
     */	
    bool match_value(String value) const;
public:
	/**
     * @brief Initiates an ip with pattern field 
     */
    Ip(String pattern);
    /**
     * @brief destruct ip 
     */
    ~Ip(); 
    /**
	   @param A string with the ip rule to build
     * @brief Returns true iff the rule is valid and theres success
       @return boolean 
     */
    bool set_value(String val);
    
};

#endif
