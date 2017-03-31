#include <catch.hpp>

#include "../../src/HTMLParser/HTMLParser.hpp"
#include "../../src/HTMLElements/HTMLElement.hpp"
#include "../../src/Document/Document.hpp"

TEST_CASE("HTMLParser tests")
{
    HTMLParser parser;

    SECTION("Constructing Document from string")
    {
        std::wstring simple_html = L"<!DOCTYPE html><html><head></head>"
            "<body><p>Test</p></body></html>";
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
        REQUIRE(root_children.size() == 2);

        std::shared_ptr<HTMLElement> head = root_children.at(0);
        std::shared_ptr<HTMLElement> body = root_children.at(1);

        CHECK(head->get_title() == L"head");
        CHECK(body->get_title() == L"body");

        std::vector<std::shared_ptr<HTMLElement>> body_children = 
            body->get_children();

        CHECK(head->get_children().size() == 0);
        REQUIRE(body_children.size() == 1);

        std::shared_ptr<HTMLElement> p = body_children.at(0);
        std::vector<std::shared_ptr<HTMLElement>> p_children = 
            p->get_children();
        REQUIRE(p_children.size() == 1);
    }
}
