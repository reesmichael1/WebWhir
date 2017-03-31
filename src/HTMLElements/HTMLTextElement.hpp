#ifndef HTMLTEXTELEMENT_H
#define HTMLTEXTELEMENT_H

#include "HTMLElement.hpp"
#include "../HTMLParser/tokens/HTMLToken.hpp"

class HTMLTextElement : public HTMLElement
{
    public:
        HTMLTextElement();
        bool is_text_node();
        std::wstring get_text();
        void add_char(std::shared_ptr<HTMLToken> char_token);

    protected:
        std::wstring text;
};

#endif
