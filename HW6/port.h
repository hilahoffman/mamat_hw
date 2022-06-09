#ifndef PORT_H
#define PORT_H

#include "string.h"
#include "field.h"

class Port : public Field {
	int down; /* the min port that's ok*/
	int up;   /* the max port that's ok*/
protected:
    /**
	   @param A string with the port to check
     * @brief Returns true iff "value" matches the value of this 
     	which mean in between down and up
       @return boolean 
     */	
    bool match_value(String value) const;
public:
	/**
     * @brief Initiates a port with pattern field 
     */
    Port(String pattern);
    /**
     * @brief destruct ip 
     */
    ~Port();
    /**
	   @param A string with the port rule to build
     * @brief Returns true iff the rule is valid and theres success
       @return boolean 
     */
    bool set_value(String val);
};

#endif
