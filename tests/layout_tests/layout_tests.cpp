#include <catch.hpp>
#include <vector>

#include "../../src/Layout/Layout.hpp"
#include "../../src/HTMLParser/HTMLParser.hpp"
#include "../../src/Document/Document.hpp"

std::vector<int> zero_vector{0, 0};

TEST_CASE("Constructing Layout from strings")
{
    Layout layout;
    layout.set_width(500);

    SECTION("No line breaks required by string")
    {
        SECTION("Adding a single string")
        {
            layout.add_string(L"Hello world!");

            auto boxes = layout.get_boxes();

            REQUIRE(boxes.size() == 1);
            CHECK(boxes.at(0).get_width() == 89);
            CHECK(boxes.at(0).get_height() == 11);
            CHECK(boxes.at(0).get_coordinates() == zero_vector);
            CHECK(boxes.at(0).get_box_string() == L"Hello world!");
        }

        SECTION("Adding multiple strings")
        {
            layout.add_string(L"Hello world!");
            layout.add_string(L" This is the second string.");

            auto boxes = layout.get_boxes();

            REQUIRE(boxes.size() == 1);
            CHECK(boxes.at(0).get_width() == 275);
            CHECK(boxes.at(0).get_height() == 14);
            CHECK(boxes.at(0).get_coordinates() == zero_vector);
            CHECK(boxes.at(0).get_box_string() == 
                    L"Hello world! This is the second string.");
        }
    }

    SECTION("Line breaks required")
    {
        SECTION("Long string with spaces")
        {
            std::wstring lorem_ipsum = L"Lorem ipsum dolor sit amet, "
                "consectetur adipiscing elit. Suspendisse in mi sagittis, "
                "venenatis ex quis, fringilla sapien.";
            std::wstring line1 = L"Lorem ipsum dolor sit amet, "
                "consectetur adipiscing elit.";
            std::wstring line2 = L"Suspendisse in mi sagittis, "
                    "venenatis ex quis, fringilla sapien.";

            layout.add_string(lorem_ipsum);

            auto boxes = layout.get_boxes();

            REQUIRE(boxes.size() == 2);
            CHECK(boxes.at(0).get_width() == 412);
            CHECK(boxes.at(0).get_height() == 14);
            CHECK(boxes.at(0).get_box_string() == line1);
            CHECK(boxes.at(1).get_width() == 442);
            CHECK(boxes.at(1).get_height() == 14);
            CHECK(boxes.at(1).get_box_string() == line2);
        }

        SECTION("Single very long string")
        {
            // TODO
        }
    }
}

TEST_CASE("Constructing Layout from Documents")
{
    HTMLParser parser;
    Layout layout;
    layout.set_width(500);

    std::wstring no_p(L"<!DOCTYPE html><html><head>"
            "</head><body>Test</body></html>");
    std::wstring with_p(L"<!DOCTYPE html><html><head></head>"
            "<body><p>Test</p></body></html>");
    std::wstring two_p(L"<!DOCTYPE html><html><head></head>"
            "<body><p>Test</p><p>Test 2</p></body></html>");
    std::wstring p_long(L"<!DOCTYPE html><html><head></head><body>"
        "<p>This is a string with a line break in "
        "just the right place to catch a bug."
        "</p></body></html>");

    SECTION("No paragraph nodes in Document")
    {
        Document doc = parser.construct_document_from_string(no_p);
        layout.construct_from_document(doc);

        auto boxes = layout.get_boxes();

        REQUIRE(boxes.size() == 1);
        CHECK(boxes.at(0).get_box_string() == L"Test");
        CHECK(boxes.at(0).get_width() == 32);
        CHECK(boxes.at(0).get_height() == 11);
        CHECK(boxes.at(0).get_coordinates() == zero_vector);
    }

    SECTION("With paragraph nodes in Document")
    {
        SECTION("One paragraph node in document")
        {
            Document doc = parser.construct_document_from_string(with_p);
            layout.construct_from_document(doc);

            auto boxes = layout.get_boxes();

            REQUIRE(boxes.size() == 1);
            CHECK(boxes.at(0).get_box_string() == L"Test");
            CHECK(boxes.at(0).get_width() == 32);
            CHECK(boxes.at(0).get_height() == 11);
            CHECK(boxes.at(0).get_coordinates() == zero_vector);
        }

        SECTION("Two paragraph nodes in document")
        {
            Document doc = parser.construct_document_from_string(two_p);
            layout.construct_from_document(doc);
            std::vector<int> two_p_coordinates{0, 25};

            auto boxes = layout.get_boxes();

            REQUIRE(boxes.size() == 2);
            CHECK(boxes.at(0).get_box_string() == L"Test");
            CHECK(boxes.at(0).get_coordinates() == zero_vector);
            CHECK(boxes.at(1).get_box_string() == L"Test 2");
            CHECK(boxes.at(1).get_coordinates() == two_p_coordinates);
        }

        SECTION("Line breaks in paragraph nodes with one word on second line")
        {
            std::vector<int> second_line_coordinates{0, 16};
            Document doc = parser.construct_document_from_string(p_long);
            layout.construct_from_document(doc);
            layout.set_view(sf::View());
            layout.update();

            auto boxes = layout.get_boxes();

            REQUIRE(boxes.size() == 2);
            CHECK(boxes.at(0).get_box_string() == L"This is a string with a "
                    "line break in just the right place to catch a");
            CHECK(boxes.at(0).get_coordinates() == zero_vector);
            CHECK(boxes.at(0).is_visible());
            CHECK(boxes.at(1).get_box_string() == L"bug.");
            CHECK(boxes.at(1).get_coordinates() == second_line_coordinates);
            CHECK(boxes.at(1).is_visible());
        }
    }
}
