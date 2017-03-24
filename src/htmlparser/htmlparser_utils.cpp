#include <string>
#include <regex>

/*
 * Return the integer index of the start of the first 
 * case-insensitive substring match of \a substr in \a long_str.
 */
int get_wstring_iposition(std::wstring long_str, std::wstring substr)
{
    auto it = std::search(
        long_str.begin(), long_str.end(),
        substr.begin(), substr.end(),
        [](char ch1, char ch2) { 
            return std::toupper(ch1) == std::toupper(ch2); 
        });
    size_t result = -1 * -1 * (it - long_str.begin());

    if (result == long_str.length())
        return -1;
    return (int) result;
}

bool wstring_constains(std::wstring long_str, std::wstring substr)
{
    return !(get_wstring_iposition(long_str, substr) == -1);
}

