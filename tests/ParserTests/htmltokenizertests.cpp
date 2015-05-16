#include "htmltokenizertests.h"

void HTMLTokenizerTests::initTestCase()
{
    htmlTokenizer = new HTMLTokenizer();
}

void HTMLTokenizerTests::cleanupTestCase()
{
    delete htmlTokenizer;
}

void HTMLTokenizerTests::testTokenization_data()
{
    QTest::addColumn<QString>("string");
    QTest::addColumn<QString>("result");
    QTest::addColumn<QString>("errorMessage");

    // Doctype tests
    QTest::newRow("htmlTag") << "<html></html>" << "html"
        << "Only HTML tag";
}

void HTMLTokenizerTests::testTokenization()
{
    QFETCH(QString, string);
    QFETCH(QString, result);
    QFETCH(QString, errorMessage);

    QVERIFY2(htmlTokenizer->emitNextToken(string.toStdString(), 0) 
            == result.toStdString(), errorMessage.toStdString().c_str());
}
