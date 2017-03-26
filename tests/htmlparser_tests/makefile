CC=g++
CXXFLAGS=-std=c++14 -Wall -pedantic
LIBS=/usr/lib/libboost_regex.a
ODIR=../build
SDIR=../../src

_OBJS = HTMLToken.o StartToken.o EndToken.o DoctypeToken.o CommentToken.o \
		HTMLTokenizer.o HTMLTokenizer_utils.o 
OBJS = $(patsubst %,$(ODIR)/%,$(_OBJS))

all: $(OBJS) htmlvalidation_tests htmltokenization_tests

$(ODIR)/HTMLToken.o: $(SDIR)/HTMLParser/tokens/HTMLToken.cpp \
	$(SDIR)/HTMLParser/tokens/HTMLToken.hpp
	$(CC) $(CXXFLAGS) -c $(SDIR)/HTMLParser/tokens/HTMLToken.cpp \
		-o $(ODIR)/HTMLToken.o

$(ODIR)/StartToken.o: $(SDIR)/HTMLParser/tokens/StartToken.cpp \
	$(SDIR)/HTMLParser/tokens/StartToken.hpp
	$(CC) $(CXXFLAGS) -c $(SDIR)/HTMLParser/tokens/StartToken.cpp \
		-o $(ODIR)/StartToken.o

$(ODIR)/EndToken.o: $(SDIR)/HTMLParser/tokens/EndToken.cpp \
	$(SDIR)/HTMLParser/tokens/EndToken.hpp
	$(CC) $(CXXFLAGS) -c $(SDIR)/HTMLParser/tokens/EndToken.cpp \
		-o $(ODIR)/EndToken.o

$(ODIR)/DoctypeToken.o: $(SDIR)/HTMLParser/tokens/DoctypeToken.cpp \
	$(SDIR)/HTMLParser/tokens/DoctypeToken.hpp
	$(CC) $(CXXFLAGS) -c $(SDIR)/HTMLParser/tokens/DoctypeToken.cpp \
		-o $(ODIR)/DoctypeToken.o

$(ODIR)/CommentToken.o: $(SDIR)/HTMLParser/tokens/CommentToken.cpp \
	$(SDIR)/HTMLParser/tokens/CommentToken.hpp
	$(CC) $(CXXFLAGS) -c $(SDIR)/HTMLParser/tokens/CommentToken.cpp \
		-o $(ODIR)/CommentToken.o

$(ODIR)/HTMLTokenizer_utils.o: $(SDIR)/HTMLParser/HTMLTokenizer_utils.cpp
	$(CC) $(CXXFLAGS) -c $(SDIR)/HTMLParser/HTMLTokenizer_utils.cpp \
		-o $(ODIR)/HTMLTokenizer_utils.o

$(ODIR)/HTMLTokenizer.o: $(SDIR)/HTMLParser/HTMLTokenizer.hpp \
	$(SDIR)/HTMLParser/HTMLTokenizer_utils.cpp \
	$(SDIR)/HTMLParser/HTMLTokenizer.cpp $(ODIR)/HTMLToken.o \
	$(ODIR)/StartToken.o $(ODIR)/EndToken.o $(ODIR)/CommentToken.o
	$(CC) $(CXXFLAGS) -c $(SDIR)/HTMLParser/HTMLTokenizer.cpp \
		-o $(ODIR)/HTMLTokenizer.o

htmlvalidation_tests: htmlvalidation_tests.cpp $(OBJS)
	$(CC) $(CXXFLAGS) -o htmlvalidation_tests htmlvalidation_tests.cpp \
		../test_skeleton.o $(OBJS) $(LIBS)

htmltokenization_tests: htmltokenization_tests.cpp $(OBJS)
	$(CC) $(CXXFLAGS) -o htmltokenization_tests htmltokenization_tests.cpp \
		../test_skeleton.o $(OBJS) $(LIBS)

clean:
	$(RM) $(ODIR)/*.o
	$(RM) htmltokenization_tests htmlvalidation_tests
