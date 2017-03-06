// Testing this is hard

#include <QVector>

#include "htmltoken.h"
#include "htmlelementtests.h"

HTMLElementTests::HTMLElementTests()
{
}

void HTMLElementTests::initTestCase()
{
    htmlElement = new HTMLElement;
}

void HTMLElementTests::cleanupTestCase()
{
    delete htmlElement;
}

void HTMLElementTests::testCreatingElements()
{
}

void HTMLElementTests::testCreatingElements_data()
{
}
