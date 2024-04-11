CXX = g++                                                                                                           
CXXFLAGS = -g -O0 -Wall -std=gnu++2b

TARGET = test

all: $(TARGET)

clean: 
	rm -rf *.o $(TARGET)
                                                                                                                     
# .cpp, .cc, .cxx, .C                                                                                               
# .h, .hh, .hpp                                                                                                     
string : string.cpp 
	$(CXX) $(CXXFLAGS) -c string.cpp -o string.o

list : list.cpp 
	$(CXX) $(CXXFLAGS) -c list.cpp -o list.o

main : main.cpp  
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

# $(TARGET): main string list
# 	$(CXX) $(CXXFLAGS) string.o list.o main.o -o $(TARGET)

$(TARGET): main list string
	$(CXX) $(CXXFLAGS) list.o string.o main.o -o $(TARGET)