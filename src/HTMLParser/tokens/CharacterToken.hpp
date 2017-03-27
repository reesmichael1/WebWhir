#ifndef CHARACTERTOKEN_H
#define CHARACTERTOKEN_H

#include "HTMLToken.hpp"

class CharacterToken : public HTMLToken
{
    public:
        CharacterToken(wchar_t char_to_set);
        bool is_char_token();
        wchar_t get_char();
        void set_char(wchar_t char_to_set);

    protected:
        wchar_t token_char;
};

#endif
