CC=g++
CXXFLAGS=-std=c++14 -Wall -pedantic
LDFLAGS=-lboost_regex -lsfml-system -lsfml-graphics
ODIR=../build/obj
BDIR=../build/bin
SDIR=../../src
OBJS=$(ODIR)/*.o

all: $(OBJS) $(BDIR)/htmlvalidation_tests $(BDIR)/htmltokenization_tests \
	$(BDIR)/htmlparser_tests

$(BDIR)/htmlvalidation_tests: htmlvalidation_tests.cpp $(OBJS)
	$(CC) $(CXXFLAGS) htmlvalidation_tests.cpp $(OBJS) $(LDFLAGS) \
		-o $(BDIR)/htmlvalidation_tests 

$(BDIR)/htmltokenization_tests: htmltokenization_tests.cpp $(OBJS)
	$(CC) $(CXXFLAGS) htmltokenization_tests.cpp $(OBJS) $(LDFLAGS) \
		-o $(BDIR)/htmltokenization_tests

$(BDIR)/htmlparser_tests: htmlparser_tests.cpp $(OBJS)
	$(CC) $(CXXFLAGS) htmlparser_tests.cpp $(OBJS) $(LDFLAGS) \
		-o $(BDIR)/htmlparser_tests

clean:
	$(RM) $(BDIR)/htmlparser_tests $(BDIR)/htmlvalidation_tests \
		$(BDIR)/htmltokenization_tests
