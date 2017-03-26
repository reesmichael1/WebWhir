#include "HTMLToken.h"

HTMLToken::~HTMLToken()
{
}

std::wstring HTMLToken::get_tag_name()
{
    return tag_name;
}

void HTMLToken::add_char_to_tag_name(wchar_t next_char)
{
    tag_name.push_back(tolower(next_char));
}

void HTMLToken::set_name(std::wstring name)
{
    tag_name = name;
}
