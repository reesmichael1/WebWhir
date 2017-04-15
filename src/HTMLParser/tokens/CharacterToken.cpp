#include "CharacterToken.hpp"

CharacterToken::CharacterToken(const wchar_t &char_to_set)
{
    token_char = char_to_set;
}

bool CharacterToken::is_char_token() const
{
    return true;
}

wchar_t CharacterToken::get_char() const
{
    return token_char;
}

void CharacterToken::set_char(const wchar_t &char_to_set)
{
    token_char = char_to_set;
}
