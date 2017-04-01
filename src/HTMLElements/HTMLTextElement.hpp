#ifndef HTMLTEXTELEMENT_H
#define HTMLTEXTELEMENT_H

#include "HTMLElement.hpp"

class HTMLTextElement : public HTMLElement
{
    public:
        HTMLTextElement();
        bool is_text_node();
        void add_char(wchar_t next_char);
        void add_char(std::wstring next_char);
        std::wstring get_text();

    protected:
        std::wstring text;
};

#endif
