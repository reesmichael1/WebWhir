#include "CommentToken.hpp"

CommentToken::CommentToken()
{
    data = L"";
}

bool CommentToken::is_comment_token()
{
    return true;
}

std::wstring CommentToken::get_data()
{
    return data;
}

void CommentToken::add_char_to_data(wchar_t next_char)
{
    data.push_back(next_char);
}

void CommentToken::set_data(std::wstring data_string)
{
    data = data_string;
}
