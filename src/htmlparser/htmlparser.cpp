#include <boost/regex.hpp>
#include <algorithm>

#include "htmlparser.h"

int get_wstring_iposition(std::wstring long_str, std::wstring substr);

// A list of commonly used Unicode whitespace characters 
// In order: tab, line feed, form feed, space
std::set<wchar_t> space_chars = 
    {'\u0009', '\u000A', '\u000C', '\u0020'};

// TODO: Check HTML requirements more strictly
bool HTMLParser::is_valid_html_string(std::wstring html_string)
{
    return HTMLParser::contains_doctype(html_string) &&
           HTMLParser::contains_root_element(html_string) &&
           HTMLParser::doctype_before_root(html_string);
}

bool HTMLParser::contains_doctype(std::wstring html_string)
{
    return (get_wstring_iposition(html_string, L"<!DOCTYPE") != -1);
}

bool HTMLParser::contains_root_element(std::wstring html_string)
{
    return HTMLParser::contains_root_open(html_string) &&
           HTMLParser::contains_root_close(html_string) &&
           HTMLParser::contains_root_open_before_close(html_string);
}

bool HTMLParser::contains_root_open(std::wstring html_string)
{
    boost::wregex html_root(L"<html\\s+.*>|<html>");
    boost::wsmatch results;
    return boost::regex_search(html_string, results, html_root);
}

bool HTMLParser::contains_root_close(std::wstring html_string)
{
    return (html_string.find(L"</html>") != std::wstring::npos);
}

bool HTMLParser::contains_root_open_before_close(std::wstring html_string)
{
    return (html_string.find(L"<html") < html_string.find(L"</html>"));
}

bool HTMLParser::doctype_before_root(std::wstring html_string)
{
    return get_wstring_iposition(html_string, L"<!DOCTYPE") <
        get_wstring_iposition(html_string, L"<html");
}

Token HTMLParser::create_token_from_string(std::wstring html_string)
{
    tokenizer_state state = data_state;
    return create_token_from_string(html_string, state);
}

Token HTMLParser::create_token_from_string(std::wstring html_string, 
        HTMLParser::tokenizer_state &state)
{
    StartToken start_token = StartToken();
    EndToken end_token = EndToken();
    DoctypeToken doctype_token = DoctypeToken();

    bool current_token_is_start_token = true;

    // Can't use range-based loop, because we need to 
    // be able to look forwards/go backwards
    for (std::wstring::iterator it = html_string.begin(); 
            it != html_string.end(); ++it)
    {
        wchar_t next_char = *it;
        switch (state)
        {
            case data_state:
            {
                // TODO: implement this state
                if (next_char == '&')
                    state = char_ref_in_data_state;

                else if (next_char == '<')
                    state = tag_open_state;

                // Handle \u0000, EOF
                // else return character token
                break;
            }

            case tag_open_state:
            {
                if (next_char == '!')
                    state = markup_declaration_open_state;

                else if (next_char == '/')
                    state = end_tag_open_state;

                else if (isalpha(next_char))
                {
                    if (current_token_is_start_token)
                        start_token = StartToken(next_char);
                    else
                        end_token = EndToken(next_char);
                    std::wstring tag_name = L"";
                    state = tag_name_state;
                }

                // parse error
                else if (next_char == '?')
                    state = bogus_comment_state;

                break;
            }

            case tag_name_state:
            {
                if (space_chars.count(next_char) != 0)
                    state = before_attribute_name_state;

                else if (next_char == '/')
                    state = self_closing_start_tag_state;

                else if (next_char == '>')
                {
                    state = data_state;
                    if (current_token_is_start_token)
                        return start_token;
                    return end_token;
                }

                else if (isalpha(next_char))
                {
                    if (current_token_is_start_token)
                        start_token.add_char_to_name(next_char);
                    else
                        end_token.add_char_to_name(next_char);
                }

                // null, EOF: parse error
                
                else
                {
                    if (current_token_is_start_token)
                        start_token.add_char_to_name(next_char);
                    else
                        end_token.add_char_to_name(next_char);
                }

                break;
            }

            case char_ref_in_data_state:
                break;

            case self_closing_start_tag_state:
            {
                if (next_char == '>')
                {
                    state = data_state;
                    if (current_token_is_start_token)
                    {
                        start_token.set_self_closing(true);
                        return start_token;
                    }
                    end_token.set_self_closing(true);
                    return end_token;
                }

                // anything else: parse error
                break;
            }

            case before_attribute_name_state:
            {
                if (space_chars.count(next_char) != 0)
                    break;

                else if (next_char == '/')
                    state = self_closing_start_tag_state;

                else if (next_char == '>')
                {
                    state = data_state;
                    if (current_token_is_start_token)
                        return start_token;
                    return end_token;
                }

                // null, EOF, ", ', ?, = 
                // parse error
                
                else
                {
                    state = attribute_name_state;
                    start_token.add_to_current_attribute_name(next_char);
                }

                break;
            }

            case attribute_name_state:
            {
                if (space_chars.count(next_char) != 0)
                    state = after_attribute_name_state;

                else if (next_char == '/')
                    state = self_closing_start_tag_state;

                else if (next_char == '=')
                    state = before_attribute_value_state;

                // EOF, ", ', <, null
                // parse error
                
                else
                    start_token.add_to_current_attribute_name(next_char);

                break;
            }

            case after_attribute_name_state:
            {
                if (space_chars.count(next_char) != 0)
                    break;

                if (next_char == '/')
                    state = self_closing_start_tag_state;

                if (next_char == '=')
                    state = before_attribute_value_state;

                // null, ", ', <, EOF
                // parse error

                break;
            }

            case before_attribute_value_state:
            {
                if (space_chars.count(next_char) != 0)
                    break;

                else if (next_char == '"')
                    state = attribute_value_double_quoted_state;

                // TODO: implement this state
                else if (next_char == '&')
                    state = attribute_value_unquoted_state;

                else if (next_char == '\'')
                    state = attribute_value_single_quoted_state;

                else if (next_char == '>')
                {
                    // parse error
                    state = data_state;
                    if (current_token_is_start_token)
                        return start_token;
                    return end_token;
                }

                // <, =, `, EOF
                // parse error

                else
                {
                    start_token.add_to_current_attribute_name(next_char);
                    state = attribute_value_unquoted_state; 
                }

                break;
            }

            case attribute_value_double_quoted_state:
            {
                if (next_char == '"')
                    state = after_attribute_value_quoted_state;

                else if (next_char == '&')
                    // TODO: implement this state
                    state = char_ref_in_attribute_value_state;

                // null, EOF: parse error
                
                else
                    start_token.add_to_current_attribute_value(next_char);

                break;
            }

            case attribute_value_single_quoted_state:
            {
                if (next_char == '\'')
                    state = after_attribute_value_quoted_state;

                // TODO: handle this state
                else if (next_char == '&')
                    state = char_ref_in_attribute_value_state;

                // EOF: parse error

                else
                    start_token.add_to_current_attribute_value(next_char);

                break;
            }

            case attribute_value_unquoted_state:
            {
                if (space_chars.count(next_char) != 0)
                    state = before_attribute_value_state;

                // TODO: implement this state
                else if (next_char == '&')
                    state = char_ref_in_attribute_value_state;

                else if (next_char == '>')
                {
                    state = data_state;
                    
                    if (current_token_is_start_token)
                        return start_token;
                    return end_token;
                }

                // null, ", ', <, =, `, EOF: parse error
                
                else
                    start_token.add_to_current_attribute_value(next_char);

                break;
            }

            case after_attribute_value_quoted_state:
            {
                start_token.process_current_attribute();
                
                if (space_chars.count(next_char) != 0)
                    state = before_attribute_name_state;

                else if (next_char == '/')
                    state = self_closing_start_tag_state;

                else if (next_char == '>')
                {
                    state = data_state;

                    if (current_token_is_start_token)
                        return start_token;
                    return end_token;
                }

                // EOF, anything else: parse error
                break;
            }

            case bogus_comment_state:
                break;

            case markup_declaration_open_state:
            {
                // Check if we are in a comment
                std::wstring next_seven_chars(it, it + 7);

                if (get_wstring_iposition(next_seven_chars, L"doctype") == 0)
                {
                    // 6, not 7, because for loop increments one extra step
                    it += 6;
                    state = doctype_state;
                }

                break;
            }

            case doctype_state:
            {
                if (space_chars.count(next_char) != 0)
                    state = before_doctype_name_state;

                // EOF: parse error

                else
                {
                    it--;
                    state = before_doctype_name_state;
                }

                break;
            }

            case before_doctype_name_state:
            {
                if (space_chars.count(next_char) != 0)
                    break;

                if (next_char == '>')
                {
                    state = data_state;
                    doctype_token.set_quirks_required(true);
                    return doctype_token;
                }

                // EOF: parse error

                else
                {
                    doctype_token = DoctypeToken(next_char);
                    state = doctype_name_state;
                    break;
                }
            }

            case doctype_name_state:
            {
                if (space_chars.count(next_char) != 0)
                {
                    state = after_doctype_name_state;
                    doctype_token.set_is_name_set(true);
                    break;
                }

                else if (next_char == '>')
                {
                    state = data_state;
                    doctype_token.set_is_name_set(true);
                    return doctype_token;
                }

                // null, EOF: parse error

                doctype_token.add_to_name(next_char);
                break;
            }

            case after_doctype_name_state:
            {
                if (space_chars.count(next_char) != 0)
                    break;

                // EOF: parse error
                
                // More exotic doctypes are not yet supported
                doctype_token.set_quirks_required(true);
                state = bogus_doctype_state;
                break;
            }

            case bogus_doctype_state:
            {
                if (next_char == '>')
                {
                    state = data_state;
                    return doctype_token;
                }

                // EOF: reconsume
                break;
            }

            case end_tag_open_state:
            {
                if (isalpha(next_char))
                {
                    end_token = EndToken(next_char);
                    current_token_is_start_token = false;
                    state = tag_name_state;
                }

                // anything else: parse error

                break;
            }

            default:
            {
                break;
            }
        }
    }

    // Shouldn't get here
    if (current_token_is_start_token)
        return start_token;
    return end_token;
}
