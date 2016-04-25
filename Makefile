CC	= g++-4.9 -std=c++14
CXXFLAG = -O0 -Wall -Wextra -W -ggdb3 -pthread -I.
STATICLIB = gtest-x64.a

test: test.o $(STATICLIB)
	$(CC) $^ -o $@ $(CXXFLAG)

test.o: test.cpp Queue.hpp RWLock.hpp Queue.impl.hpp
	$(CC) $< -c $(CXXFLAG)
	
clean:
	rm -f *.o test

rebuild: clean test

.PHONY:	clean rebuild test
