CC 			= g++-4.9 -std=c++14
CXXFLAG 	= -O0 -Wall -Wextra -W -ggdb3 -pthread -I.

GTEST_HEADER= gtest/*.h gtest/internal/*.h
GTEST_SRC 	= gsrc/*.cc gsrc/*.h $(GTEST_HEADER)

test 		: test.o gtest_main.a
	$(CC) $^ -o $@ $(CXXFLAG)

test.o 		: test.cpp Queue.hpp
	$(CC) $< -c $(CXXFLAG)
	
gtest_main.a: gtest-all.o gtest_main.o
	$(AR) $(ARFLAGS) $@ $^

gtest-all.o : $(GTEST_SRC)
	$(CC) $(CXXFLAG) -c gsrc/gtest-all.cc

gtest_main.o: $(GTEST_SRC)
	$(CC) $(CXXFLAG) -c gsrc/gtest_main.cc

clean		:
	rm -f *.o test

rebuild		:	clean test

.PHONY		:	clean rebuild
