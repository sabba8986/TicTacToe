CC = clang++
C_CC = gcc
CFLAGS = -ansi -Wall -g -O0 -Wwrite-strings -Wshadow -pedantic-errors -fstack-protector-all -Wextra -std=c++11 

all: ttt

ttt: main.o Board.o
	@$(CC) -o ttt -fuse-ld=lld main.o Board.o

main.o: main.cpp 
	@$(C_CC) $(CFLAGS) -c main.cpp

Board.o: Board.cpp Board.hpp
	@$(CC) $(CFLAGS) -c Board.cpp

libgame_api.a: Board.o interface_functions.o
	@ar -rcs libgame_api.a Board.o interface_functions.o

interface_functions.o: interface_functions.cpp interface_functions.hpp Board.hpp
	@$(CC) $(CFLAGS) -c interface_functions.cpp


clean: 
	@rm -f *.o ttt


