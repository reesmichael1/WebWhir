CC=g++
CXXFLAGS=-std=c++14 -Wall -pedantic
LIBS=/usr/lib/libboost_regex.a

all: htmlparser_tests

htmlparser_tests: htmlparser_tests.cpp ../../src/htmlparser/htmlparser.h \
	../../src/htmlparser/htmlparser.cpp \
	../../src/htmlparser/htmlparser_utils.cpp
	$(CC) $(CXXFLAGS) -o htmlparser_tests htmlparser_tests.cpp \
		../test_skeleton.o ../../src/htmlparser/htmlparser.cpp \
		../../src/htmlparser/htmlparser_utils.cpp $(LIBS)
