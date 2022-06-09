#definitions
CXX=g++
CXXLINK=g++
CXXFLAGS=-g -Wall -std=c++11
OBJS=field.o string.o ip.o port.o 
EXEC=firewall.exe
RM= $(wildcard *.o) libfirewall.so firewall.exe 

#linking
$(EXEC): libfirewall.so main.o
	$(CXXLINK) main.o -o $(EXEC) -lfirewall -linput -L.

#first rule: create the library
libfirewall.so: $(OBJS)
	$(CXXLINK) -shared $(OBJS) -o libfirewall.so -L.

#other dependencies: compile to o file

main.o: main.cpp string.h field.h ip.h port.h
	$(CXX) $(CXXFLAGS) -c main.cpp

string.o: string.cpp string.h
	$(CXX) $(CXXFLAGS) -c -fpic string.cpp
	
field.o: field.cpp field.h string.h
	$(CXX) $(CXXFLAGS) -c -fpic field.cpp
	
ip.o: ip.cpp ip.h field.h string.h
	$(CXX) $(CXXFLAGS) -c -fpic ip.cpp
	
port.o: port.cpp port.h field.h string.h
	$(CXX) $(CXXFLAGS) -c -fpic port.cpp

#clean rule
clean:
	rm -rf $(RM)