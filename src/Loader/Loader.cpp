#include <iostream>
#include <fstream>
#include <locale>
#include <codecvt>
#include <boost/algorithm/string.hpp>

#include "Loader.hpp"

std::wstring Loader::load_from_file(std::string filename)
{
    std::ifstream html_file(filename);

    if (!html_file.fail())
    {
        std::string line;

        std::wstring html_string;

        while (std::getline(html_file, line))
        {
            boost::trim(line);
            html_string += 
                std::wstring_convert<std::codecvt_utf8<wchar_t>>()
                .from_bytes(line);
        }

        return html_string;
    }
    
    std::cerr << "Error: could not open file " << filename << std::endl;
    return L"";
}
