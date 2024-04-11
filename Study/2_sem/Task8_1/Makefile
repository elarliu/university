CXX = g++                                                                                                           
CXXFLAGS = -g -O0 -Wall -std=gnu++2b

TARGET = test

all: $(TARGET)

clean: 
	rm -rf *.o $(TARGET)
                                                                                                                     
# .cpp, .cc, .cxx, .C                                                                                               
# .h, .hh, .hpp                                                                                                     
# matrix : matrix.cpp 
# 	$(CXX) -std=gnu++2b -c matrix.cpp -o matrix.o
# main : main.cpp  
# 	$(CXX) -std=gnu++2b -c main.cpp -o main.o

$(TARGET): main.cpp
	$(CXX) $(CXXFLAGS) main.cpp -o $(TARGET)