#definitions
CC=gcc
CFLAGS=-Wall -std=c99 -g
CCLINK=$(CC)
OBJS= grades.o
RM= $(wildcard *.o) libgrades.so

#first rule: linking
libgrades.so: grades.o
	$(CCLINK) -shared grades.o -llinked-list -L./ -o libgrades.so 

#other dependencies: compile to o file
grades.o: grades.c grades.h
	$(CC) -c -fpic grades.c

#clean rule
clean:
	rm -rf $(RM)