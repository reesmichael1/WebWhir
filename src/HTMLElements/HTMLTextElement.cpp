#include "HTMLTextElement.hpp"

HTMLTextElement::HTMLTextElement()
{
    title = L"";
    text = L"";
}

bool HTMLTextElement::is_text_node()
{
    return true;
}

std::wstring HTMLTextElement::get_text()
{
    return text;
}

void HTMLTextElement::add_char(std::shared_ptr<HTMLToken> char_token)
{
    text.push_back(char_token->get_char());
}
