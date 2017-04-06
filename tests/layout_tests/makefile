CC=g++
CXXFLAGS=-std=c++14 -Wall -pedantic
ODIR=../build/obj
BDIR=../build/bin
SDIR=../../src
LDFLAGS=-lsfml-graphics -lsfml-system

_OBJS = Layout.o Box.o
OBJS = $(patsubst %,$(ODIR)/%,$(_OBJS))

all: $(OBJS) $(BDIR)/layout_tests

$(ODIR)/Layout.o: $(SDIR)/Layout/Layout.hpp $(SDIR)/Layout/Layout.cpp
	$(CC) $(CXXFLAGS) $(SDIR)/Layout/Layout.cpp -c -o $(ODIR)/Layout.o

$(ODIR)/Box.o: $(SDIR)/Layout/Box.*
	$(CC) $(CXXFLAGS) $(SDIR)/Layout/Box.cpp -c -o $(ODIR)/Box.o

$(BDIR)/layout_tests: $(OBJS) layout_tests.cpp
	$(CC) $(CXXFLAGS) $(OBJS) $(LDFLAGS) layout_tests.cpp ../test_skeleton.o \
		-o $(BDIR)/layout_tests

clean: 
	$(RM) $(OBJS) $(BDIR)/layout_tests
