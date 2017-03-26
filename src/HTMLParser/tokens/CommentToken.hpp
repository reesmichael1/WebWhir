#ifndef COMMENTTOKEN_H
#define COMMENTTOKEN_H

#include "HTMLToken.hpp"

class CommentToken : public HTMLToken
{
    public:
        CommentToken();
        bool is_comment_token();
        std::wstring get_data();
        void add_char_to_data(wchar_t next_char);
        void set_data(std::wstring data_string);

    protected:
        std::wstring data;
};

#endif
