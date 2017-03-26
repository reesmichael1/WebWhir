CC=g++
CXXFLAGS=-std=c++14 -Wall -pedantic
LIBS=/usr/lib/libboost_regex.a
ODIR=../build
SDIR=../../src

_OBJS = HTMLToken.o StartToken.o EndToken.o DoctypeToken.o htmlparser.o \
		htmlparser_utils.o
OBJS = $(patsubst %,$(ODIR)/%,$(_OBJS))

all: $(OBJS) htmlvalidation_tests htmltokenization_tests

$(ODIR)/HTMLToken.o: $(SDIR)/htmlparser/tokens/HTMLToken.cpp \
	$(SDIR)/htmlparser/tokens/HTMLToken.h
	$(CC) $(CXXFLAGS) -c $(SDIR)/htmlparser/tokens/HTMLToken.cpp \
		-o $(ODIR)/HTMLToken.o

$(ODIR)/StartToken.o: $(SDIR)/htmlparser/tokens/StartToken.cpp \
	$(SDIR)/htmlparser/tokens/StartToken.h
	$(CC) $(CXXFLAGS) -c $(SDIR)/htmlparser/tokens/StartToken.cpp \
		-o $(ODIR)/StartToken.o

$(ODIR)/EndToken.o: $(SDIR)/htmlparser/tokens/EndToken.cpp \
	$(SDIR)/htmlparser/tokens/EndToken.h
	$(CC) $(CXXFLAGS) -c $(SDIR)/htmlparser/tokens/EndToken.cpp \
		-o $(ODIR)/EndToken.o

$(ODIR)/DoctypeToken.o: $(SDIR)/htmlparser/tokens/DoctypeToken.cpp \
	$(SDIR)/htmlparser/tokens/DoctypeToken.h
	$(CC) $(CXXFLAGS) -c $(SDIR)/htmlparser/tokens/DoctypeToken.cpp \
		-o $(ODIR)/DoctypeToken.o

$(ODIR)/htmlparser_utils.o: $(SDIR)/htmlparser/htmlparser_utils.cpp
	$(CC) $(CXXFLAGS) -c $(SDIR)/htmlparser/htmlparser_utils.cpp \
		-o $(ODIR)/htmlparser_utils.o

$(ODIR)/htmlparser.o: $(SDIR)/htmlparser/htmlparser.h \
	$(SDIR)/htmlparser/htmlparser_utils.cpp \
	$(SDIR)/htmlparser/htmlparser.cpp $(ODIR)/HTMLToken.o
	$(CC) $(CXXFLAGS) -c $(SDIR)/htmlparser/htmlparser.cpp \
		-o $(ODIR)/htmlparser.o

htmlvalidation_tests: htmlvalidation_tests.cpp $(OBJS)
	$(CC) $(CXXFLAGS) -o htmlvalidation_tests htmlvalidation_tests.cpp \
		../test_skeleton.o $(OBJS) $(LIBS)

htmltokenization_tests: htmltokenization_tests.cpp $(OBJS)
	$(CC) $(CXXFLAGS) -o htmltokenization_tests htmltokenization_tests.cpp \
		../test_skeleton.o $(OBJS) $(LIBS)

clean:
	$(RM) $(ODIR)/*.o
