CC = gcc
CFLAGS = -g -o0
TARGET = sh

all: $(TARGET)

clean: 
	rm -rf *.o $(TARGET)

tree: tree.c
	$(CC) -c tree.c -o tree.o

list: list.c
	$(CC) -c list.c -o list.o

error: error.c
	$(CC) -c error.c -o error.o

shell: shell.c
	$(CC) -c shell.c -o shell.o

$(TARGET): list shell tree error
	$(CC) $(CFLAGS) error.o tree.o list.o shell.o -o $(TARGET)

# runvalg:
# 	rlwrap valgrind ./$(TARGET)

runvalg:
	rlwrap valgrind --leak-check=full ./$(TARGET)

run:
	rlwrap ./$(TARGET)

# prog.out: prog.c char_list.out 
# 	gcc -o unite.out char_list.out prog.out