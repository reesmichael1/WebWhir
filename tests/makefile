CC=g++
CXXFLAGS=-std=c++14 -Wall -pedantic

.PHONY: htmlparser_tests

all: tests

tests: htmlparser_tests test_skeleton.o

test_skeleton.o: test_skeleton.cpp
	$(CC) $(CXXFLAGS) -c test_skeleton.cpp

htmlparser_tests: 
	+$(MAKE) -C htmlparser_tests

clean:
	$(RM) htmlparser_tests/htmltokenization_tests \
		htmlparser_tests/htmlvalidation_tests
