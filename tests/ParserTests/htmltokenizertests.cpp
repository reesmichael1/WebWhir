#include "htmltokenizertests.h"
#include "htmltoken.h"

// Keep Qt from whining about not recognizing the type
typedef QHash<QString, QString> attributesType; 
Q_DECLARE_METATYPE(attributesType);

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
    QTest::addColumn<int>("start");
    QTest::addColumn<QString>("result");
    QTest::addColumn<QString>("errorMessage");

    // Tag name tests
    QTest::newRow("htmlTag") << "<html></html>" << 0 << "html"
        << "Only HTML tag";
    QTest::newRow("closingHtmlTag") << "<html></html>" << 6 << "html"
        << "Closing tag of <html></html>";
}

void HTMLTokenizerTests::testTokenization()
{
    QFETCH(QString, string);
    QFETCH(int, start);
    QFETCH(QString, result);
    QFETCH(QString, errorMessage);

    QVERIFY2(htmlTokenizer->emitNextToken(string.toStdString(), 
            start).getTokenName() == result.toStdString(), 
            errorMessage.toStdString().c_str());
}

void HTMLTokenizerTests::testEndTags_data()
{
    QTest::addColumn<QString>("htmlString");    
    QTest::addColumn<int>("start");
    QTest::addColumn<bool>("isEndTag");
    QTest::addColumn<QString>("errorMessage");

    QTest::newRow("onlyEndTag") << "</html>" << 0 << true
        << "Only </html>";
    QTest::newRow("noEndTag") << "<html>" << 0 << false
        << "Only <html>";
    QTest::newRow("twoTags") << "<html></html>" << 6 << true
        << "Both opening and closing tags are present";
    QTest::newRow("manyTags") << "<html><head><title></title></head></html>"
        << 19 << true << "Several opening and closing tags are nested";
}

void HTMLTokenizerTests::testEndTags()
{
    QFETCH(QString, htmlString);
    QFETCH(int, start);
    QFETCH(bool, isEndTag);
    QFETCH(QString, errorMessage);

    QVERIFY2(htmlTokenizer->emitNextToken(htmlString.toStdString(),
                start).getIsEndTagToken() == isEndTag, 
            errorMessage.toStdString().c_str());
}

void HTMLTokenizerTests::testAttributes_data()
{
    //Q_DECLARE_METATYPE(std::string);

    QTest::addColumn<QString>("htmlString");
    QTest::addColumn<int>("start");
    QTest::addColumn<attributesType>("attributes");
    QTest::addColumn<QString>("errorMessage");


    attributesType noAttributesMap;
    QTest::newRow("noAttributes") << "<html></html>" << 0 
        << noAttributesMap << "All attributes should be empty";
    attributesType oneAttributeMap;
    oneAttributeMap["name1"] = "value1";
    oneAttributeMap.insert("name1", "value1");
    QTest::newRow("oneAttribute") << "<tag name1=\"value1\">" << 0
        << oneAttributeMap 
        << "The attribute \"name1\" should have the value \"value1\"";
    attributesType twoAttributesMap;
    //twoAttributesMap["name1"] = "value1";
    twoAttributesMap.insert("name1", "value1");
    twoAttributesMap.insert("name2", "value2");
    QTest::newRow("twoAttributes") << 
        "<tag name1=\"value1\" name2=\"value2\">" << 0 << twoAttributesMap
        << "Two distinct attributes in original string";
}

void HTMLTokenizerTests::testAttributes()
{
    QFETCH(QString, htmlString);
    QFETCH(int, start);
    QFETCH(attributesType, attributes);
    QFETCH(QString, errorMessage);

    HTMLToken nextToken = htmlTokenizer->emitNextToken(
            htmlString.toStdString(), start);

    std::vector<QString> attributeNames;
    std::vector<QString> attributeValues;

    for (auto kv : nextToken.getAttributes())
    {
        attributeNames.push_back(QString::fromStdString(kv.first));
        attributeValues.push_back(QString::fromStdString(kv.second));
    }
    
    // For now, just check that attribute has correct names and values
    QVERIFY2(std::is_permutation(attributeNames.begin(), 
                attributeNames.end(), 
                attributes.keys().toVector().toStdVector().begin())
            && std::is_permutation(attributeValues.begin(),
               attributeValues.end(),  
               attributes.values().toVector().toStdVector().begin()), 
            errorMessage.toStdString().c_str());
}
