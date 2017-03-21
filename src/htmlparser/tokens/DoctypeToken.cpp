#include "DoctypeToken.h"

DoctypeToken::DoctypeToken()
{
    require_quirks = false;
    name_set = false;
    public_identifier_set = false;
    system_identifier_set = false;
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
