#include <catch.hpp>
#include <vector>

#include "../../src/Layout/Layout.hpp"

std::vector<int> ten_vector{10, 10};

TEST_CASE("Constructing layout from strings")
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
            CHECK(boxes.at(0).get_width() == 82);
            CHECK(boxes.at(0).get_height() == 11);
            CHECK(boxes.at(0).get_coordinates() == ten_vector);
            CHECK(boxes.at(0).get_box_string() == L"Hello world!");
        }

        SECTION("Adding multiple strings")
        {
            layout.add_string(L"Hello world!");
            layout.add_string(L" This is the second string.");

            auto boxes = layout.get_boxes();

            REQUIRE(boxes.size() == 1);
            CHECK(boxes.at(0).get_width() == 265);
            CHECK(boxes.at(0).get_height() == 14);
            CHECK(boxes.at(0).get_coordinates() == ten_vector);
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
            CHECK(boxes.at(0).get_width() == 400);
            CHECK(boxes.at(0).get_height() == 14);
            CHECK(boxes.at(0).get_box_string() == line1);
            CHECK(boxes.at(1).get_width() == 432);
            CHECK(boxes.at(1).get_height() == 14);
            CHECK(boxes.at(1).get_box_string() == line2);
        }

        SECTION("Single very long string")
        {
            // TODO
        }
    }
}
