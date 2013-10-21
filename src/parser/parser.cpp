#include "htmlreader.h"
#include "elements/HTMLHeadElement.h"
#include "elements/HTMLBodyElement.h"
#include "elements/HTMLBElement.h"
#include "elements/HTMLParagraphElement.h"
#include "elements/HTMLImgElement.h"
#include "elements/HTMLHrElement.h"
#include "elements/HTMLLiElement.h"
#include "elements/HTMLUlElement.h"
#include "elements/HTMLIElement.h"

RenderNode* HTMLReader::createNode(std::string nodeName,
                                   parseState &currentState,
                                   std::string::iterator &i,
                                   std::string HTMLFilepath)


{
    RenderNode *node = new RenderNode;

    if (nodeName == "html")
    {
        node = createFirstNode();
    }
    else if (nodeName == "p")
    {
        node = createParagraphNode(currentState);
    }
    else if (nodeName == "b")
    {
        node = createBNode(currentState);
    }
    else if (nodeName == "i")
    {
        node = createINode(currentState);
    }
    else if (nodeName == "img")
    {
        node = createImageNode(currentState, i, HTMLFilepath);
    }
    else if (nodeName == "hr")
    {
        node = createHrNode();
    }
    else if (nodeName == "li")
    {
        node = createLiNode(currentState);
    }
    else if (nodeName == "ul")
    {
        node = createUlNode();
    }
    else if (nodeName == "head")
    {
        node = createHeadNode();
        currentParentNode = webpage->getFirstNode();
    }

    else if (nodeName == "body")
    {
        node = createBodyNode();
        currentParentNode = webpage->getFirstNode();
    }

    return node;
}

RenderNode* HTMLReader::createFirstNode()
{
    //This node is necessary because it acts as the parent node
    //for both the head and body nodes.
    RenderNode *firstNode = new RenderNode;
    firstNode->setParentNode(NULL);
    firstNode->setTypeOfRenderNode("html");
    firstNode->setIsOpen(true);

    return firstNode;
}

ParagraphNode* HTMLReader::createParagraphNode(parseState &currentState)
{

    currentState = text;

    HTMLParagraphElement pElement;
    ParagraphNode *paragraphNode = new ParagraphNode;
    paragraphNode = pElement.returnNode();
    paragraphNode->setIsOpen(true);

    return paragraphNode;
}

BNode* HTMLReader::createBNode(parseState &currentState)
{
    currentState = text;

    HTMLBElement bElement;
    BNode *bNode = new BNode;
    bNode = bElement.returnNode();
    bNode->setIsOpen(true);

    return bNode;
}

INode* HTMLReader::createINode(parseState &currentState)
{
    currentState = text;

    HTMLIElement iElement;
    INode *iNode = new INode;
    iNode = iElement.returnNode();
    iNode->setIsOpen(true);

    return iNode;
}

ImageNode* HTMLReader::createImageNode(parseState &currentState,
                                       std::string::iterator &i,
                                       std::string HTMLFilepath)
{
    //Read through the tag and collect the necessary information to create
    //the node.

    std::string imageAttributes;
    HTMLImgElement imgElement;

    while (currentState == endTagName)
    {
        imageAttributes = "";
        if (i[0] == '>')
        {
            currentState = endTagOpen;
        }

        else
        {
            while (isspace(*i))
            {
                i++;
            }

            while (*i != '=')
            {
                imageAttributes.push_back(i[0]);
                i++;
            }

            if (*i == '=')
            {

                if (imageAttributes == "src")
                {
                    while (*i != '\"')
                    {
                        i++;
                    }

                    i++;

                    std::string sourcePath;
                    sourcePath = HTMLFilepath;

                    //Nothing would please me more than to use C++ 11 features
                    //like back() and pop_back() here. Hopefully, I can make
                    //this transition in time.
                    while (sourcePath.at(sourcePath.length() - 1) != '/')
                    {
                        sourcePath = sourcePath.substr(0, sourcePath.length() - 1);
                    }

                    while (*i != '\"')
                    {
                        sourcePath.push_back(i[0]);
                        i++;
                    }

                    imgElement.setSourcePath(sourcePath);
                }

                else if (imageAttributes == "alt")
                {
                    while (*i != '\"')
                    {
                        i++;
                    }

                    i++;

                    std::string altText;

                    while (*i != '\"')
                    {
                        altText.push_back(i[0]);
                        i++;
                    }

                    imgElement.setAltText(altText);

                }
            }
        }

        i++;
    }

    //Reset to text if the <img> is inline.
    if (isalpha(*i) || isspace(*i))
    {
        currentState = text;
    }

    //Subtract one to correct the overreach at the end of the while loop.
    i--;

    ImageNode *image = new ImageNode;
    image = imgElement.returnNode();
    image->setIsOpen(false);

    return image;
}

HorizontalRuleNode* HTMLReader::createHrNode()
{
    HTMLHrElement hrElement;
    HorizontalRuleNode *hrNode = new HorizontalRuleNode;
    hrNode = hrElement.returnNode();
    hrNode->setIsOpen(false);

    return hrNode;
}

ListNode* HTMLReader::createLiNode(parseState &currentState)
{
    currentState = text;

    HTMLLiElement liElement;
    ListNode* listNode = new ListNode;
    listNode = liElement.returnNode();
    listNode->setIsOpen(true);

    return listNode;
}

UlNode* HTMLReader::createUlNode()
{
    HTMLUlElement ulElement;
    UlNode *ulNode = new UlNode;
    ulNode = ulElement.returnNode();
    ulNode->setIsOpen(true);

    return ulNode;
}

HeadNode* HTMLReader::createHeadNode()
{
    HTMLHeadElement headElement;
    HeadNode *head = new HeadNode;
    head = headElement.returnNode();
    head->setIsOpen(true);

    return head;
}

BodyNode* HTMLReader::createBodyNode()
{
    HTMLBodyElement bodyElement;
    BodyNode *body = new BodyNode;

    body = bodyElement.returnNode();
    body->setIsOpen(true);

    return body;

}
