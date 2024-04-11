CC = gcc


all: echo pwd ls ln cmp od

clean: 
	rm -rf *.o echo pwd ls ln cmp od

echo: echo.c
	$(CC) echo.c -o echo

pwd: pwd.c
	$(CC) pwd.c -o pwd

ls: ls.c
	$(CC) ls.c -o ls

ln: ln.c
	$(CC) ln.c -o ln

cmp: cmp.c
	$(CC) cmp.c -o cmp

od: od.c
	$(CC) od.c -o od

# $(TARGET): char_list.o prog.o
# 	$(CC) char_list.o prog.o -o $(TARGET)

# prog.out: prog.c char_list.out 
# 	gcc -o unite.out char_list.out prog.out