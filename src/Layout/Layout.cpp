#include <boost/algorithm/string.hpp>
#include <stack>

#include "Layout.hpp"

#define PARAGRAPH_BREAK_PADDING 14

Layout::Layout()
{
    cursor_x = 0;
    cursor_y = 0;
    boxes = {};

    is_font_set = font.loadFromFile("/usr/share/fonts/TTF/DejaVuSerif.ttf");

    text.setCharacterSize(14);
    text.setFont(font);

    is_last_box_finalized = false;
}

void push_remaining_children(std::vector<std::shared_ptr<HTMLElement>> c, 
        std::stack<std::vector<std::shared_ptr<HTMLElement>>> &r)
{
    if (c.size() <= 1)
        r.push({});

    else
    {
        std::vector<std::shared_ptr<HTMLElement>> 
            rest_children(c.begin() + 1, c.end());

        r.push(rest_children);
    }
}

void Layout::construct_from_document(Document document)
{
    boxes = {};
    cursor_x = 0;
    cursor_y = 0;

    auto node = document.get_elements().front();

    std::stack<std::vector<std::shared_ptr<HTMLElement>>> remaining_children;
    auto root_children = node->get_children();

    push_remaining_children(node->get_children(), remaining_children);

    while (true)
    {
        if (node->is_text_node())
            add_string(node->get_text());

        else if (node->is_paragraph_node())
        {
            if (boxes.size() > 0)
            {
                is_last_box_finalized = true;
                cursor_y += PARAGRAPH_BREAK_PADDING;
            }
        }

        if (node->get_children().size() > 0)
        {
            node = node->get_children().front();
            push_remaining_children(node->get_children(), remaining_children);
        }

        else
        {
            while (remaining_children.top().size() == 0)
            {
                remaining_children.pop();

                if (remaining_children.size() == 0)
                    break;
            }

            if (remaining_children.size() == 0)
                break;

            auto current_children = remaining_children.top();
            remaining_children.pop();

            node = current_children.front();
            push_remaining_children(current_children, remaining_children);
        }
    }
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
        if (!is_last_box_finalized)
        {
            current_box = boxes.at(boxes.size() - 1);
            boxes.pop_back();
        }

        else
            current_box.set_coordinates({cursor_x, cursor_y});
    }

    else
    {
        current_box.set_coordinates({cursor_x, cursor_y});
        is_last_box_finalized = false;
    }

    std::wstring current_string = current_box.get_box_string(); 
    std::wstring old_string = current_string;

    std::vector<int> coordinates = current_box.get_coordinates();

    for (const auto& word : words)
    {
        current_string += word;
        text.setString(current_string);

        if (cursor_x + text.getLocalBounds().width < width)
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
            is_last_box_finalized = true;

            current_box = Box();

            cursor_y += current_box.get_height();
            current_string = word;
            old_string = current_string;
        }


        old_string = current_string;
        current_string += L" ";
    }

    boxes.push_back(current_box);
    cursor_y += text.getLocalBounds().height;
}

std::vector<Box> Layout::get_boxes()
{
    return boxes;
}
