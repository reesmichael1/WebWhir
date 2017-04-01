CC=g++
CXXFLAGS=-std=c++14 -Wall -pedantic
DIRS=htmlparser_tests
ODIR=build/obj

.PHONY: htmlparser_tests

all: tests

tests: htmlparser_tests $(ODIR)/test_skeleton.o

$(ODIR)/test_skeleton.o: test_skeleton.cpp
	$(CC) $(CXXFLAGS) -c test_skeleton.cpp -o $(ODIR)/test_skeleton.o

htmlparser_tests: 
	+$(MAKE) -C htmlparser_tests

clean:
	for d in $(DIRS); do (cd $$d; $(MAKE) clean ); done
