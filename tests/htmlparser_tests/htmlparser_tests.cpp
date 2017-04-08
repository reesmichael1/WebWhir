#include <catch.hpp>

#include "../../src/HTMLParser/HTMLParser.hpp"
#include "../../src/HTMLElements/HTMLElement.hpp"
#include "../../src/Document/Document.hpp"

TEST_CASE("HTMLParser tests")
{
    HTMLParser parser;

    SECTION("Constructing Document from string")
    {
        SECTION("One text node inside body")
        {
            std::wstring simple_html = L"<!DOCTYPE html><html><head></head>"
                "<body>Test</body></html>";
            Document doc = parser.construct_document_from_string(simple_html);

            CHECK(doc.get_document_type().get_name() == L"html");
            CHECK_FALSE(doc.requires_quirks_mode());

            // Use REQUIRE instead of CHECK 
            // to avoid trying to access out of range
            auto elements = doc.get_elements();
            REQUIRE(elements.size() == 1);

            auto root = elements.front();

            CHECK(root->get_title() == L"html");
            auto root_children = root->get_children();

            // head is not inserted into root element
            REQUIRE(root_children.size() == 1);

            auto body = root_children.at(0);

            CHECK(body->get_title() == L"body");

            auto body_children = body->get_children();

            REQUIRE(body_children.size() == 1);

            auto text = body_children.at(0);
            auto text_children = text->get_children();

            REQUIRE(text_children.size() == 0);
            CHECK(text->get_text() == L"Test");
        }

        SECTION("Two text nodes inside p nodes")
        {
            std::wstring simple_html = L"<!DOCTYPE html><html><head></head>"
                "<body><p>Test 1</p><p>Test 2</p></body></html>";
            Document doc = parser.construct_document_from_string(simple_html);

            CHECK(doc.get_document_type().get_name() == L"html");
            CHECK_FALSE(doc.requires_quirks_mode());

            // Use REQUIRE instead of CHECK 
            // to avoid trying to access out of range
            auto elements = doc.get_elements();
            REQUIRE(elements.size() == 1);

            auto root = elements.front();

            CHECK(root->get_title() == L"html");
            auto root_children = root->get_children();

            // head is not inserted into root element
            REQUIRE(root_children.size() == 1);

            auto body = root_children.at(0);

            CHECK(body->get_title() == L"body");

            auto body_children = body->get_children();

            REQUIRE(body_children.size() == 2);

            auto p1 = body_children.at(0);
            auto p1_children = p1->get_children();

            auto p2 = body_children.at(1);
            auto p2_children = p2->get_children();

            REQUIRE(p1_children.size() == 1);
            REQUIRE(p2_children.size() == 1);

            auto p1_text = p1_children.at(0);
            auto p2_text = p2_children.at(0);

            CHECK(p1_text->get_text() == L"Test 1");
            CHECK(p2_text->get_text() == L"Test 2");
        }
    }
}
