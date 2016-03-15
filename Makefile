CC 			= icc
CXXFLAG 	= -O0 -Wall -Wextra -g -std=c++14 -pthread -I. -openmp

Queue		: Queue.o
	$(CC) $< -o $@ $(CXXFLAG)
	
Queue.o 	: Queue.cpp
	$(CC) $< -o $@ $(CXXFLAG) -c

clean		:
	rm -f test.o Queue.o

rebuild		:	clean test

.PHONY		:	clean rebuild
