#include "EndToken.h"

#include <iostream>

EndToken::EndToken()
{
    self_closing = false;
    tag_name = L"";
}

EndToken::EndToken(wchar_t token_name)
{
    self_closing = false;
    tag_name = tolower(token_name);
}

std::wstring EndToken::get_tag_name()
{
    return tag_name;
}

void EndToken::add_char_to_name(wchar_t next_char)
{
    tag_name.push_back(tolower(next_char));
}

bool EndToken::is_self_closing()
{
    return self_closing;
}

void EndToken::set_self_closing(bool closing)
{
    self_closing = closing;
}

std::map<std::wstring, std::wstring> EndToken::get_attributes()
{
    std::wcerr << "PARSE ERROR: Attempt to access attributes " << 
        " in end token" << std::endl;
    return {};
}

void EndToken::set_name(std::wstring name)
{
    tag_name = name;
}

void EndToken::add_to_current_attribute_name(wchar_t next_char)
{
    // If we get here, this is a parse error
    return;
}

void EndToken::add_to_current_attribute_value(wchar_t next_char)
{
    // If we get here, this is a parse error
    return;
}

bool EndToken::contains_attribute(std::wstring attribute_name)
{
    // EndTokens should never have attributes
    return false;
}

std::wstring EndToken::get_attribute_value(std::wstring attribute_name)
{
    std::wcerr << "PARSE ERROR: Attempt to access attribute " << 
        attribute_name << " in end token" << std::endl;
    return NULL;
}

void EndToken::process_current_attribute()
{
    // If we get here, this is a parse error
    return;
}
