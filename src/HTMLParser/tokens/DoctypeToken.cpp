#include "DoctypeToken.hpp"

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
    tag_name = tolower(token_name);
}

bool DoctypeToken::quirks_required() const
{
    return require_quirks;
}

bool DoctypeToken::is_public_identifier_set() const
{
    return public_identifier_set;
}

bool DoctypeToken::is_system_identifier_set() const
{
    return system_identifier_set;
}

bool DoctypeToken::is_name_set() const
{
    return name_set;
}

void DoctypeToken::set_is_name_set(bool is_set)
{
    name_set = is_set;
}

std::wstring DoctypeToken::get_public_identifier() const
{
    return public_identifier;
}

std::wstring DoctypeToken::get_system_identifier() const
{
    return system_identifier;
}

void DoctypeToken::set_quirks_required(bool required)
{
    require_quirks = required;
}

bool DoctypeToken::is_doctype_token() const
{
    return true;
}
