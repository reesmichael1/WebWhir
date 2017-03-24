#include "DoctypeToken.h"

DoctypeToken::DoctypeToken()
{
    require_quirks = false;
    name_set = false;
    public_identifier_set = false;
    system_identifier_set = false;
}

DoctypeToken::DoctypeToken(wchar_t token_name)
{
    require_quirks = false;
    name_set = false;
    public_identifier_set = false;
    system_identifier_set = false;
    name = tolower(token_name);
}

bool DoctypeToken::quirks_required()
{
    return require_quirks;
}

bool DoctypeToken::is_public_identifier_set()
{
    return public_identifier_set;
}

bool DoctypeToken::is_system_identifier_set()
{
    return system_identifier_set;
}

bool DoctypeToken::is_name_set()
{
    return name_set;
}

void DoctypeToken::set_is_name_set(bool is_set)
{
    name_set = is_set;
}

std::wstring DoctypeToken::get_name()
{
    return name;
}

std::wstring DoctypeToken::get_public_identifier()
{
    return public_identifier;
}

std::wstring DoctypeToken::get_system_identifier()
{
    return system_identifier;
}

void DoctypeToken::set_quirks_required(bool required)
{
    require_quirks = required;
}

void DoctypeToken::add_to_name(wchar_t char_to_add)
{
    name.push_back(tolower(char_to_add));
}
