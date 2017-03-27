#include "CharacterToken.hpp"

CharacterToken::CharacterToken(wchar_t char_to_set)
{
    token_char = char_to_set;
}

bool CharacterToken::is_char_token()
{
    return true;
}

wchar_t CharacterToken::get_char()
{
    return token_char;
}

void CharacterToken::set_char(wchar_t char_to_set)
{
    token_char = char_to_set;
}
