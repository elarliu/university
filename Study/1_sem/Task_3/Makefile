CC = gcc
TARGET = united

all: $(TARGET)

clean: 
	rm -rf *.o $(TARGET)

char_list.o: char_list.c
	$(CC) -c char_list.c -o char_list.o

prog.o: prog.c
	$(CC) -c prog.c -o prog.o

$(TARGET): char_list.o prog.o
	$(CC) char_list.o prog.o -o $(TARGET)

# prog.out: prog.c char_list.out 
# 	gcc -o unite.out char_list.out prog.out