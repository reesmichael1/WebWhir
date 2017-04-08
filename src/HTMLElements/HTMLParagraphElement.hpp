#ifndef HTMLPARAGRAPHELEMENT_H
#define HTMLPARAGRAPHELEMENT_H

#include "HTMLElement.hpp"

class HTMLParagraphElement : public HTMLElement
{
    public:
        HTMLParagraphElement();
        bool is_paragraph_node();
};

#endif
