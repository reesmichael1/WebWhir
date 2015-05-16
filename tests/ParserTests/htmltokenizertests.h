#ifndef HTMLTOKENIZERTESTS_H
#define HTMLTOKENIZERTESTS_H

#include <QtTest>

#include "htmltokenizer.h"

class HTMLTokenizerTests : public QObject
{
    Q_OBJECT

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void testTokenization_data();
    void testTokenization();

private:
    HTMLTokenizer *htmlTokenizer;
};

#endif // HTMLTOKENIZERTESTS_H
