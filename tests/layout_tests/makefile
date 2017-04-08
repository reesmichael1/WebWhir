CC=g++
CXXFLAGS=-std=c++14 -Wall -pedantic
ODIR=../build/obj
BDIR=../build/bin
SDIR=../../src
LDFLAGS=-lsfml-graphics -lsfml-system -lboost_regex
OBJS=$(ODIR)/*.o

all: $(OBJS) $(BDIR)/layout_tests

$(BDIR)/layout_tests: $(OBJS) layout_tests.cpp
	$(CC) $(CXXFLAGS) $(OBJS) $(LDFLAGS) layout_tests.cpp \
		-o $(BDIR)/layout_tests

clean: 
	$(RM) $(BDIR)/layout_tests
