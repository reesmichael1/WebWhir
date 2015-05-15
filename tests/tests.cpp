#include <QtTest>
#include "ParserTests/htmlparsertests.h"

int main()
{
    HTMLParserTests parserTests;
    QTest::qExec(&parserTests);
}
