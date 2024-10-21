CXX = /opt/homebrew/Cellar/gcc/14.2.0/bin/g++-14
CXXFLAGS = -fopenmp -Wall -std=gnu++2b
# CXXFLAGS = -fopenmp -g -o0 -Wall -std=gnu++2b
                                                                                                                     
# .cpp, .cc, .cxx, .C                                                                                               
# .h, .hh, .hpp                                                                                                     
mult : mult.cpp
main : main.cpp


TARGET = exec

all: $(TARGET)

clean: 
	rm -rf *.o $(TARGET)

mult: mult.cpp
	$(CXX) $(CXXFLAGS) -c mult.cpp -o mult.o

main: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

$(TARGET): main mult
	$(CXX) $(CXXFLAGS) mult.o main.o -o $(TARGET)