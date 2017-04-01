#include <catch.hpp>

#include "../../src/HTMLParser/HTMLParser.hpp"
#include "../../src/HTMLElements/HTMLElement.hpp"
#include "../../src/Document/Document.hpp"

#include <iostream>

TEST_CASE("HTMLParser tests")
{
    HTMLParser parser;

    SECTION("Constructing Document from string")
    {
        std::wstring simple_html = L"<!DOCTYPE html><html><head></head>"
            "<body>Test</body></html>";
        Document doc = parser.construct_document_from_string(simple_html);

        CHECK(doc.get_document_type().get_name() == L"html");
        CHECK_FALSE(doc.requires_quirks_mode());

        // Use REQUIRE instead of CHECK to avoid trying to access out of range
        std::list<std::shared_ptr<HTMLElement>> elements = doc.get_elements();
        REQUIRE(elements.size() == 1);

        std::shared_ptr<HTMLElement> root = elements.front();

        CHECK(root->get_title() == L"html");
        std::vector<std::shared_ptr<HTMLElement>> root_children = 
            root->get_children();

        // head is not inserted into root element
        REQUIRE(root_children.size() == 1);

        std::shared_ptr<HTMLElement> body = root_children.at(0);

        CHECK(body->get_title() == L"body");

        std::vector<std::shared_ptr<HTMLElement>> body_children = 
            body->get_children();

        REQUIRE(body_children.size() == 1);

        std::shared_ptr<HTMLElement> text = body_children.at(0);
        std::vector<std::shared_ptr<HTMLElement>> text_children = 
            text->get_children();

        REQUIRE(text_children.size() == 0);
        CHECK(text->get_text() == L"Test");
    }
}
