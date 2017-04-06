#include <boost/algorithm/string.hpp>

#include "Layout.hpp"

Layout::Layout()
{
    cursor_x = 10;
    cursor_y = 10;
    boxes = {};

    is_font_set = font.loadFromFile("/usr/share/fonts/TTF/DejaVuSans.ttf");

    text.setCharacterSize(14);
    text.setFont(font);
}

void Layout::set_width(int new_width)
{
    width = new_width;
}

void Layout::add_string(std::wstring string)
{
    std::vector<std::wstring> words;
    boost::split(words, string, boost::is_any_of(L" "));

    Box current_box;
    if (boxes.size() > 0)
    {
        current_box = boxes.at(boxes.size() - 1);
        boxes.pop_back();
    }

    else
        current_box.set_coordinates({cursor_x, cursor_y});

    std::wstring current_string = current_box.get_box_string(); 
    std::wstring old_string = current_string;

    std::vector<int> coordinates = current_box.get_coordinates();

    for (const auto& word : words)
    {
        current_string += word;
        text.setString(current_string);

        if (cursor_x + text.getLocalBounds().width < width - 10)
        {
            current_box.set_box_string(current_string);
            current_box.set_width(text.getLocalBounds().width);
            current_box.set_height(text.getLocalBounds().height);
        }

        else
        {
            text.setString(old_string);
            current_box.set_box_string(old_string);
            current_box.set_width(text.getLocalBounds().width);
            current_box.set_height(text.getLocalBounds().height);
            boxes.push_back(current_box);

            current_box = Box();

            text.setString("");
            cursor_x = 10;
            cursor_y += current_box.get_height();
            current_string = word;
            old_string = current_string;
        }

        old_string = current_string;
        current_string += L" ";
    }

    boxes.push_back(current_box);
}

std::vector<Box> Layout::get_boxes()
{
    return boxes;
}
