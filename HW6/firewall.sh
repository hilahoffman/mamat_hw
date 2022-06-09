#!/bin/bash

# all packets in the file, removing ' ' and tabs from them 
all_packets=$(cat | tr -s ' ');

while read line; do

	line=$(echo $line | tr -d ' ' | sed -e 's/#.*//');
	
	# skip empty lines
	if [ ! -z "$line" ]; then

		# for each line update the remained packets to be all
		remained_packets=$all_packets

		# split the string into four. send each command
		# to firewall.exe with the packets that 'survived' 
		for(( index=1; index<5; index++ )) 
		do
		rule=$(echo $line | cut -d "," -f$index)
		remained_packets=$(echo "$remained_packets" | ./firewall.exe "$rule")
		done

		# update the good packet list
		good_packets+=$(echo "$remained_packets")
		good_packets+="\n"

	fi # if empty line

done <$1 # allows the bash code to read lines from the text argument

# print good packets but in sorting order, and only one time
echo -e "$good_packets" | grep -vE ^$ | tr -d ' ' | sort | uniq

