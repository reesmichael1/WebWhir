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

HTMLToken HTMLParser::create_token_from_string(std::wstring html_string)
{
    tokenizer_state state = data_state;
    return create_token_from_string(html_string, state);
}

HTMLToken HTMLParser::create_token_from_string(std::wstring html_string, 
        HTMLParser::tokenizer_state &state)
{
    HTMLToken token = HTMLToken();

    for (wchar_t next_char : html_string)
    {
        switch (state)
        {
            case data_state:
            {
                if (next_char == '&')
                {
                    // TODO: implement this state
                    state = char_ref_in_data_state;
                    break;
                }
                else if (next_char == '<')
                {
                    state = tag_open_state;
                    break;
                }
                // Handle \u0000, EOF
                // else return character token
                break;
            }

            case tag_open_state:
            {
                if (next_char == '!')
                {
                    state = markup_declaration_open_state;
                    break;
                }
                else if (next_char == '/')
                {
                    state = end_tag_open_state;
                    break;
                }
                else if (isalpha(next_char))
                {
                    token = HTMLToken();
                    std::wstring tag_name = L"";
                    tag_name.push_back(tolower(next_char));
                    token.set_name(tag_name);
                    state = tag_name_state;
                }
                else if (next_char == '?')
                {
                    // parse error
                    state = bogus_comment_state;
                    break;
                }
                break;
            }

            case tag_name_state:
            {
                if (space_chars.count(next_char) != 0)
                {
                    state = before_attribute_name_state;
                    break;
                }
                else if (next_char == '/')
                {
                    state = self_closing_start_tag_state;
                    break;
                }
                else if (next_char == '>')
                {
                    state = data_state;
                    return token;
                }
                else if (isalpha(next_char))
                {
                    std::wstring tag_name = token.get_tag_name();
                    tag_name.push_back(tolower(next_char));
                    token.set_name(tag_name);
                    break;
                }

                // null, EOF: parse error
                
                else
                {
                    std::wstring tag_name = token.get_tag_name() + 
                        std::wstring(&next_char);
                    token.set_name(tag_name);
                }

                break;
            }

            case char_ref_in_data_state:
            {
                break;
            }

            case self_closing_start_tag_state:
            {
                if (next_char == '>')
                {
                    state = data_state;
                    token.set_self_closing(true);
                    return token;
                }

                // anything else: parse error
            }

            case before_attribute_name_state:
            {
                if (space_chars.count(next_char) != 0)
                    break;
                else if (next_char == '/')
                {
                    state = self_closing_start_tag_state;
                    break;
                }
                else if (next_char == '>')
                {
                    state = data_state;
                    return token;
                }

                // null, EOF, ", ', ?, = 
                // parse error
                
                else
                {
                    state = attribute_name_state;
                    token.add_to_current_attribute_name(next_char);
                    break;
                }
            }

            case attribute_name_state:
            {
                if (space_chars.count(next_char) != 0)
                {
                    state = after_attribute_name_state;
                    break;
                }

                else if (next_char == '/')
                {
                    state = self_closing_start_tag_state;
                    break;
                }

                else if (next_char == '=')
                {
                    state = before_attribute_value_state;
                    break;
                }

                // EOF, ", ', <, null
                // parse error
                
                else
                {
                    token.add_to_current_attribute_name(next_char);
                    break;
                }
            }

            case after_attribute_name_state:
            {
                if (space_chars.count(next_char) != 0)
                    break;

                if (next_char == '/')
                {
                    state = self_closing_start_tag_state;
                    break;
                }

                if (next_char == '=')
                {
                    state = before_attribute_value_state;
                }

                // null, ", ', <, EOF
                // parse error

                break;
            }

            case before_attribute_value_state:
            {
                if (space_chars.count(next_char) != 0)
                    break;

                else if (next_char == '"')
                {
                    state = attribute_value_double_quoted_state;
                    break;
                }

                else if (next_char == '&')
                {
                    // TODO: implement this state
                    state = attribute_value_unquoted_state;
                    // do not break -- need to reconsume character
                }

                else if (next_char == '\'')
                {
                    state = attribute_value_single_quoted_state;
                    break;
                }

                else if (next_char == '>')
                {
                    // parse error
                    state = data_state;
                    return token;
                }

                // <, =, `, EOF
                // parse error

                else
                {
                    token.add_to_current_attribute_name(next_char);
                    state = attribute_value_unquoted_state; 
                    break;
                }
            }

            case attribute_value_double_quoted_state:
            {
                if (next_char == '"')
                {
                    state = after_attribute_value_quoted_state;
                    break;
                }

                else if (next_char == '&')
                {
                    // TODO: implement this state
                    state = char_ref_in_attribute_value_state;
                    break;
                }

                // null, EOF: parse error
                
                else
                {
                    token.add_to_current_attribute_value(next_char);
                }

                break;
            }

            case attribute_value_single_quoted_state:
            {
                if (next_char == '\'')
                {
                    state = after_attribute_value_quoted_state;
                    break;
                }

                else if (next_char == '&')
                {
                    // TODO: handle this state
                    state = char_ref_in_attribute_value_state;
                }

                // EOF: parse error

                else
                {
                    token.add_to_current_attribute_value(next_char);
                    break;
                }

                break;
            }

            case attribute_value_unquoted_state:
            {
                if (space_chars.count(next_char) != 0)
                {
                    state = before_attribute_value_state;
                    break;
                }

                else if (next_char == '&')
                {
                    // TODO: implement this state
                    state = char_ref_in_attribute_value_state;
                }

                else if (next_char == '>')
                {
                    state = data_state;
                    return token;
                }

                // null, ", ', <, =, `, EOF: parse error
                
                else
                {
                    token.add_to_current_attribute_value(next_char);
                    break;
                }

                break;
            }

            case after_attribute_value_quoted_state:
            {
                token.process_current_attribute();
                
                if (space_chars.count(next_char) != 0)
                {
                    state = before_attribute_name_state;
                    break;
                }

                else if (next_char == '/')
                {
                    state = self_closing_start_tag_state;
                }

                else if (next_char == '>')
                {
                    state = data_state;
                    return token;
                }

                // EOF, anything else: parse error
                break;
            }

            case bogus_comment_state:
                break;

            default:
            {
                break;
            }
        }
    }

    return token;
}
