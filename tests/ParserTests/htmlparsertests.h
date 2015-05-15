#ifndef HTMLPARSERTESTS_H
#define HTMLPARSERTESTS_H

#include <QString>
#include <QtTest>

#include "htmlparser.h"

class HTMLParserTests : public QObject
{
    Q_OBJECT

public:
    HTMLParserTests();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void testHTMLValidation();
    void testHTMLValidation_data();

private:
    HTMLParser *htmlParser;
};

#endif // HTMLPARSERTESTS_H
