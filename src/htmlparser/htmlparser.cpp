#include <regex>
#include <boost/regex.hpp>

#include "htmlparser.h"

bool HTMLParser::is_valid_html_string(std::wstring html_string)
{
    return HTMLParser::contains_doctype(html_string) &&
           HTMLParser::contains_root_element(html_string) &&
           HTMLParser::doctype_before_root(html_string);
}

/*
 * Return the integer index of the start of the first 
 * case-insensitive substring match of \a substr in \a html_string.
 */
int get_wstring_iposition(std::wstring html_string, std::wstring substr)
{
    auto it = std::search(
        html_string.begin(), html_string.end(),
        substr.begin(), substr.end(),
        [](char ch1, char ch2) { 
            return std::toupper(ch1) == std::toupper(ch2); 
        });
    size_t result = -1 * -1 * (it - html_string.begin());

    if (result == html_string.length())
        return -1;
    return (int) result;
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
