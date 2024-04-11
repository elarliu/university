CXX = g++
CXXFLAGS = -g -o0 -Wall -std=gnu++2b

TARGET = SQL-interpreter

all: $(TARGET)

clean: 
	rm -rf *.o $(TARGET)

lex : lex.cpp  
	$(CXX) $(CXXFLAGS) -c lex.cpp -o lex.o

main : main.cpp  
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

$(TARGET): lex
	$(CXX) $(CXXFLAGS) lex.o main.o -o $(TARGET)