#include "HTMLToken.h"

HTMLToken::HTMLToken()
{
    self_closing = false;
    attributes = {};
    tag_name = L"";
}

std::wstring HTMLToken::get_tag_name()
{
    return tag_name;
}

bool HTMLToken::is_self_closing()
{
    return self_closing;
}

std::map<std::wstring, std::wstring> HTMLToken::get_attributes()
{
    return attributes;
}
