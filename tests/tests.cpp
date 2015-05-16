#include <QtTest>
#include "ParserTests/htmlparsertests.h"
#include "ParserTests/htmltokenizertests.h"

int main()
{
    HTMLParserTests parserTests;
    QTest::qExec(&parserTests);

    HTMLTokenizerTests tokenizerTests;
    QTest::qExec(&tokenizerTests);
}
