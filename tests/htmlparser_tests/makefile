CC=g++
CXXFLAGS=-std=c++14 -Wall -pedantic
LIBS=/usr/lib/libboost_regex.a

all: htmlvalidation_tests htmltokenization_tests

htmlvalidation_tests: htmlvalidation_tests.cpp \
	../../src/htmlparser/htmlparser.h \
	../../src/htmlparser/htmlparser.cpp \
	../../src/htmlparser/htmlparser_utils.cpp
	$(CC) $(CXXFLAGS) -o htmlvalidation_tests htmlvalidation_tests.cpp \
		../test_skeleton.o ../../src/htmlparser/htmlparser.cpp \
		../../src/htmlparser/tokens/HTMLToken.cpp \
		../../src/htmlparser/htmlparser_utils.cpp $(LIBS)

htmltokenization_tests: htmltokenization_tests.cpp \
	../../src/htmlparser/tokens/HTMLToken.h \
	../../src/htmlparser/tokens/HTMLToken.cpp \
	../../src/htmlparser/tokens/DoctypeToken.h \
	../../src/htmlparser/tokens/DoctypeToken.cpp
	$(CC) $(CXXFLAGS) -o htmltokenization_tests htmltokenization_tests.cpp \
		../test_skeleton.o ../../src/htmlparser/tokens/HTMLToken.cpp \
		../../src/htmlparser/tokens/DoctypeToken.cpp \
		../../src/htmlparser/htmlparser.cpp \
		../../src/htmlparser/htmlparser_utils.cpp $(LIBS)
