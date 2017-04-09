#include <catch.hpp>

#include "../../src/Loader/Loader.hpp"

TEST_CASE("Loading from files")
{
    Loader loader;
    std::wstring correct_html(L"<!DOCTYPE html><html><head>"
            "</head><body><p>Test</p></body></html>");

    SECTION("File with no line breaks")
    {
        auto html_string = 
            loader.load_from_file("../html_files/no_breaks.html");

        CHECK(html_string == correct_html);
    }

    SECTION("File with line breaks")
    {
        auto html_string = 
            loader.load_from_file("../html_files/with_breaks.html");

        CHECK(html_string == correct_html);
    }

    SECTION("File with line breaks and tabs")
    {
        auto html_string = loader.load_from_file("../html_files/tabs.html");

        CHECK(html_string == correct_html);
    }
}
