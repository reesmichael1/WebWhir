#ifndef CHARACTERTOKEN_H
#define CHARACTERTOKEN_H

#include "HTMLToken.hpp"

class CharacterToken : public HTMLToken
{
    public:
        CharacterToken(const wchar_t &char_to_set);
        bool is_char_token() const;
        wchar_t get_char() const;
        void set_char(const wchar_t &char_to_set);

    protected:
        wchar_t token_char;
};

#endif
