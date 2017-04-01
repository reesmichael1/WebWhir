CC=g++
CXXFLAGS=-std=c++14 -Wall -pedantic
LIBS=/usr/lib/libboost_regex.a
ODIR=../build/obj
BDIR=../build/bin
SDIR=../../src

_OBJS = HTMLToken.o StartToken.o EndToken.o DoctypeToken.o CommentToken.o \
		HTMLTokenizer.o HTMLTokenizer_utils.o CharacterToken.o Document.o \
		HTMLElement.o HTMLHeadElement.o HTMLTextElement.o HTMLBodyElement.o \
		HTMLParagraphElement.o DocumentType.o HTMLParser.o
OBJS = $(patsubst %,$(ODIR)/%,$(_OBJS))

all: $(OBJS) $(BDIR)/htmlvalidation_tests $(BDIR)/htmltokenization_tests \
	$(BDIR)/htmlparser_tests

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

$(ODIR)/CharacterToken.o: $(SDIR)/HTMLParser/tokens/CharacterToken.cpp \
	$(SDIR)/HTMLParser/tokens/CharacterToken.hpp
	$(CC) $(CXXFLAGS) -c $(SDIR)/HTMLParser/tokens/CharacterToken.cpp \
		-o $(ODIR)/CharacterToken.o

$(ODIR)/HTMLTokenizer_utils.o: $(SDIR)/HTMLParser/HTMLTokenizer_utils.cpp
	$(CC) $(CXXFLAGS) -c $(SDIR)/HTMLParser/HTMLTokenizer_utils.cpp \
		-o $(ODIR)/HTMLTokenizer_utils.o

$(ODIR)/Document.o: $(SDIR)/Document/Document.hpp \
	$(SDIR)/Document/Document.cpp
	$(CC) $(CXXFLAGS) -c $(SDIR)/Document/Document.cpp -o $(ODIR)/Document.o

$(ODIR)/DocumentType.o: $(SDIR)/Document/DocumentType.hpp \
	$(SDIR)/Document/DocumentType.cpp
	$(CC) $(CXXFLAGS) -c $(SDIR)/Document/DocumentType.cpp \
		-o $(ODIR)/DocumentType.o

$(ODIR)/HTMLElement.o: $(SDIR)/HTMLElements/HTMLElement.hpp \
	$(SDIR)/HTMLElements/HTMLElement.cpp
	$(CC) $(CXXFLAGS) -c $(SDIR)/HTMLElements/HTMLElement.cpp \
		-o $(ODIR)/HTMLElement.o

$(ODIR)/HTMLHeadElement.o: $(SDIR)/HTMLElements/HTMLHeadElement.hpp \
	$(SDIR)/HTMLElements/HTMLHeadElement.cpp
	$(CC) $(CXXFLAGS) -c $(SDIR)/HTMLElements/HTMLHeadElement.cpp \
		-o $(ODIR)/HTMLHeadElement.o

$(ODIR)/HTMLTextElement.o: $(SDIR)/HTMLElements/HTMLTextElement.hpp \
	$(SDIR)/HTMLElements/HTMLTextElement.cpp
	$(CC) $(CXXFLAGS) -c $(SDIR)/HTMLElements/HTMLTextElement.cpp \
		-o $(ODIR)/HTMLTextElement.o

$(ODIR)/HTMLBodyElement.o: $(SDIR)/HTMLElements/HTMLBodyElement.hpp \
	$(SDIR)/HTMLElements/HTMLBodyElement.cpp
	$(CC) $(CXXFLAGS) -c $(SDIR)/HTMLElements/HTMLBodyElement.cpp \
		-o $(ODIR)/HTMLBodyElement.o

$(ODIR)/HTMLParagraphElement.o: $(SDIR)/HTMLElements/HTMLParagraphElement.hpp \
	$(SDIR)/HTMLElements/HTMLParagraphElement.cpp
	$(CC) $(CXXFLAGS) -c $(SDIR)/HTMLElements/HTMLParagraphElement.cpp \
		-o $(ODIR)/HTMLParagraphElement.o

$(ODIR)/HTMLParser.o: $(SDIR)/HTMLParser/HTMLParser.hpp \
	$(SDIR)/HTMLParser/HTMLParser.cpp
	$(CC) $(CXXFLAGS) -c $(SDIR)/HTMLParser/HTMLParser.cpp \
		-o $(ODIR)/HTMLParser.o

$(ODIR)/HTMLTokenizer.o: $(SDIR)/HTMLParser/HTMLTokenizer.hpp \
	$(SDIR)/HTMLParser/HTMLTokenizer_utils.cpp \
	$(SDIR)/HTMLParser/HTMLTokenizer.cpp $(OBJS)
	$(CC) $(CXXFLAGS) -c $(SDIR)/HTMLParser/HTMLTokenizer.cpp \
		-o $(ODIR)/HTMLTokenizer.o

$(BDIR)/htmlvalidation_tests: htmlvalidation_tests.cpp $(OBJS)
	$(CC) $(CXXFLAGS) htmlvalidation_tests.cpp $(ODIR)/test_skeleton.o \
		$(OBJS) $(LIBS) -o $(BDIR)/htmlvalidation_tests 

$(BDIR)/htmltokenization_tests: htmltokenization_tests.cpp $(OBJS)
	$(CC) $(CXXFLAGS) htmltokenization_tests.cpp $(ODIR)/test_skeleton.o \
		$(OBJS) $(LIBS) -o $(BDIR)/htmltokenization_tests

$(BDIR)/htmlparser_tests: htmlparser_tests.cpp $(OBJS)
	$(CC) $(CXXFLAGS) htmlparser_tests.cpp $(ODIR)/test_skeleton.o \
		$(OBJS) $(LIBS) -o $(BDIR)/htmlparser_tests

clean:
	$(RM) $(ODIR)/*.o
	$(RM) $(BDIR)/*_tests
