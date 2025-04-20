CC = gcc
CFLAGS = -Wall -Wextra -g

all: test_ast test_jadwal

test_ast: test_ast.o ast.o
	$(CC) $(CFLAGS) -o test_ast test_ast.o ast.o

test_jadwal: test_jadwal.o ast.o
	$(CC) $(CFLAGS) -o test_jadwal test_jadwal.o ast.o

test_ast.o: test_ast.c ast.h
	$(CC) $(CFLAGS) -c test_ast.c

test_jadwal.o: test_jadwal.c ast.h
	$(CC) $(CFLAGS) -c test_jadwal.c

ast.o: ast.c ast.h
	$(CC) $(CFLAGS) -c ast.c

clean:
	rm -f test_ast test_jadwal *.o

run_ast: test_ast
	./test_ast

run_jadwal: test_jadwal
	./test_jadwal

run: test_ast test_jadwal
	./test_ast
	echo "\n------------------------\n"
	./test_jadwal 