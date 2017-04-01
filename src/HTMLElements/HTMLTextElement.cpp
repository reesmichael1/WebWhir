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

void HTMLTextElement::add_char(wchar_t next_char)
{
    text.push_back(next_char);
}

void HTMLTextElement::add_char(std::wstring next_char)
{
    text += next_char;
}
