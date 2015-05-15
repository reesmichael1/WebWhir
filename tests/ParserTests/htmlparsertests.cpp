#include "HTMLParserTests.h"

HTMLParserTests::HTMLParserTests()
{
}

void HTMLParserTests::initTestCase()
{
    htmlParser = new HTMLParser();
}

void HTMLParserTests::cleanupTestCase()
{
    delete htmlParser;
}

void HTMLParserTests::testHTMLValidation_data()
{
    QTest::addColumn<QString>("string");
    QTest::addColumn<bool>("result");
    QTest::addColumn<QString>("errorMessage");

    // Doctype tests

    QTest::newRow("capitals") << "<!DOcTYpE html><html></html>" << true 
        << "Valid HTML";
    QTest::newRow("missingFinalTag") << "<!doctype HTML><html><html>" 
        << false << "No closing tag on final html";
    QTest::newRow("noDoctype") << "<html></html>" << false << "No doctype";
    QTest::newRow("badDoctype") << "<!doc h><html></html>" << false 
        << "Misspelled doctype";
    QTest::newRow("lotsOfSpaces") << "<!doctype         html><html></html>"
        << true << "Extra spaces between !doctype and HTML.";
    QTest::newRow("noClosingBracket") << "<!doctype html<html></html>" <<
        false << "No closing bracket on doctype.";

    // Root element tests
    QTest::newRow("missingBracket1") << "<!doctype html><html</html>"
        << false << "No closing bracket on first html.";
    QTest::newRow("missingBracket2") << "<!doctype html><html></html"
        << false << "No closing bracket on first html.";
    QTest::newRow("misspelledHtml") << "<!doctype html><hml></html>"
        << false << "html is misspelled as hml.";
    QTest::newRow("noClosingRootTag") << "<!doctype html><html>"
        << false << "Closing </html> is missing.";
    QTest::newRow("noOpeningRootTag") << "<!doctype html></html>"
        << false << "Opening <html> is missing.";
}

void HTMLParserTests::testHTMLValidation()
{
    QFETCH(QString, string);
    QFETCH(bool, result);
    QFETCH(QString, errorMessage);

    QVERIFY2(htmlParser->validateHTML(string.toStdString()) == result,
           errorMessage.toStdString().c_str());
}
