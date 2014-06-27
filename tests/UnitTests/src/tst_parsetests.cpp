#include <QString>
#include <QtTest>

#include "../../../src/parser/htmlreader.h"

class ParseTests : public QObject
{
    Q_OBJECT

public:
    ParseTests();

private Q_SLOTS:
    void testCase1();
};

ParseTests::ParseTests()
{
}

void ParseTests::testCase1()
{
    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(ParseTests)

#include "tst_parsetests.moc"
