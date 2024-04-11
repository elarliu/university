CC = gcc
CFLAGS = -g -o0
TARGET = serv

all: $(TARGET)

clean: 
	rm -rf *.o $(TARGET)

# parser: parser.c
# 	$(CC) -c parser.c -o parser.o

info_list: info_list.c
	$(CC) -c info_list.c -o info_list.o

# test_modules: test_modules.c
# 	$(CC) -c test_modules.c -o test_modules.o

server: server.c
	$(CC) -c server.c -o server.o

# $(TARGET): parser info_list server
# 	$(CC) $(CFLAGS) info_list.o parser.o server.o -o $(TARGET)
$(TARGET): info_list server
	$(CC) $(CFLAGS) info_list.o server.o -o $(TARGET)

runvalg:
	rlwrap valgrind --leak-check=full ./$(TARGET)

run:
	rlwrap ./$(TARGET)
