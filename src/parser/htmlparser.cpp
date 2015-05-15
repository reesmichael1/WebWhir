#include <QString>
#include <QStringList>

#include "htmlparser.h"

// TODO for parsing:
// 1. Determine character encoding

HTMLParser::HTMLParser()
{
}

// Check that the given document conforms to the HTML syntax
// http://dev.w3.org/html5/spec-preview/syntax.html#syntax
bool HTMLParser::validateHTML(std::string htmlString)
{
    // Also need to check that no non-space characters occur 
    // outside of an element
    return hasRootElement(htmlString) && hasDoctype(htmlString);
}

bool HTMLParser::hasDoctype(std::string htmlString)
{
    // If we've gotten this far, the string has a root html element
    int rootIndex = htmlString.find("<html>");
    std::string preamble = htmlString.substr(0, rootIndex);

    while (preamble.length() > 0)
    {
        int start = preamble.find("<");
        int end = preamble.find(">");
        if (preamble.find(">") == std::string::npos) return false;
        std::string tag = preamble.substr(start + 1, end - 1);
        if (tag[0] == '!')
        {
            // My preference is to avoid using Qt objects
            // except in the interface, so I may change this
            QString tagQString = QString::fromStdString(tag).simplified();
            QStringList words = tagQString.split(' ');
            // For now, I'm going to ignore 
            // the optional doctype legacy string
            if ((QString::compare(words.at(0), "!DOCTYPE", 
                        Qt::CaseInsensitive) == 0) &&
                (QString::compare(words.at(1), "html", 
                      Qt::CaseInsensitive) == 0))
            {
                return true;
            }
        }
        preamble = preamble.substr(end + 1);
    }

    return false;
}

// Check if the html element is in the document.
// This may not be the cleanest check, but it catches most cases
bool HTMLParser::hasRootElement(std::string htmlString)
{
    int startIndex = htmlString.find("<html>");
    int endIndex = htmlString.find("</html>");
    if (htmlString.find("<html>") == std::string::npos 
            || htmlString.find("</html>") == std::string::npos) 
        return false;
    return endIndex > startIndex;
}

HTMLParser::insertionMode HTMLParser::resetInsertionMode()
{
    bool onLastNode = false;
    int lastNodePosition = openElementsStack.size() - 1;
    std::string lastNode = openElementsStack.at(lastNodePosition);

    while (true)
    {
        if (openElementsStack.size() == 1)
        {
            onLastNode = true;
            //lastNode = "context"; Will only give good HTML for now
        }
        if (lastNode == "select")
        {
            return inSelect;
        }
        if ((lastNode == "td" || lastNode == "th") && !onLastNode)
        {
            return inRow;
        }
        if (lastNode == "tr")
        {
            return inRow;
        }
        if (lastNode == "tbody" || lastNode == "thead" || 
                lastNode == "tfoot")
        {
            return inTableBody;
        }
        if (lastNode == "caption")
        {
            return inCaption;
        }
        if (lastNode == "colgroup")
        {
            return inColumnGroup;
        }
        if (lastNode == "table")
        {
            return inTable;
        }
        if (lastNode == "head")
        {
            return inBody;
        }
        if (lastNode == "body")
        {
            return inBody;
        }
        if (lastNode == "frameset")
        {
            return inFrameset;
        }
        if (lastNode == "html")
        {
            return beforeHead;
        }
        if (onLastNode)
        {
            return inBody;
        }
        lastNodePosition -= 1;
        lastNode = openElementsStack.at(lastNodePosition);
    }
}
