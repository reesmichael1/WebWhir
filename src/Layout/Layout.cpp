#include <boost/algorithm/string.hpp>
#include <stack>
#include <unordered_map>

#include "Layout.hpp"

#define PARAGRAPH_BREAK_PADDING 14
#define LEADING 2

namespace WordSizes
{
    std::unordered_map<std::wstring, int> word_lengths;
    std::unordered_map<std::wstring, int> word_heights;
}

int Layout::get_word_length(const std::wstring& word)
{
    int word_length;

    if (WordSizes::word_lengths.find(word) == WordSizes::word_lengths.end())
    {
        text.setString(word);
        word_length = text.getLocalBounds().width;
        WordSizes::word_lengths.insert({word, word_length});
    }

    else
        word_length = WordSizes::word_lengths.at(word);

    return word_length;
}

int Layout::get_word_height(const std::wstring& word)
{
    int word_height;

    if (WordSizes::word_heights.find(word) == WordSizes::word_heights.end())
    {
        text.setString(word);
        word_height = text.getLocalBounds().height;
        WordSizes::word_heights.insert({word, word_height});
    }

    else
        word_height = WordSizes::word_heights.at(word);

    return word_height;
}


Layout::Layout()
{
    cursor_x = 0;
    cursor_y = 0;
    boxes = {};

    is_font_set = font.loadFromFile("/usr/share/fonts/TTF/DejaVuSerif.ttf");

    text.setCharacterSize(14);
    text.setFont(font);

    is_last_box_finalized = false;

    if (WordSizes::word_lengths.count(L" ") == 0)
    {
        text.setString(" ");
        WordSizes::word_lengths.insert({L" ", text.getLocalBounds().width});
        WordSizes::word_heights.insert({L" ", text.getLocalBounds().height});
        text.setString("");
    }

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

void Layout::construct_from_document(Document doc)
{
    boxes = {};
    cursor_x = 0;
    cursor_y = 0;

    document = doc;

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

    int space_length = WordSizes::word_lengths.at(L" ");
    int space_height = WordSizes::word_heights.at(L" ");
    int box_height = space_height;
    int box_length = 0;
    int word_length, word_height;

    Box current_box;
    if (boxes.size() > 0)
    {
        if (!is_last_box_finalized)
        {
            current_box = boxes.at(boxes.size() - 1);
            boxes.pop_back();
            box_length = current_box.get_width();
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

        word_length = get_word_length(word);
        word_height = get_word_height(word);

        if (cursor_x + box_length + space_length + word_length < width)
        {
            box_length += space_length + word_length;
            if (word_height > box_height)
                box_height = word_height;

            current_box.set_box_string(current_string);
        }

        else
        {
            current_box.set_box_string(old_string);
            current_box.set_width(box_length);
            current_box.set_height(box_height);
            boxes.push_back(current_box);
            is_last_box_finalized = true;
            cursor_y += box_height + LEADING;

            current_box = Box();

            box_length = word_length;
            box_height = word_height;

            current_string = word;
            old_string = current_string;
            current_box.set_box_string(current_string);
            current_box.set_coordinates({cursor_x, cursor_y});
        }

        current_box.set_width(box_length);
        current_box.set_height(box_height);

        old_string = current_string;
        current_string += L" ";
    }

    // If we hit the last word, then we added an extra space to the length
    if (!is_last_box_finalized)
    {
        box_length -= space_length;
        current_box.set_width(box_length);
    }

    boxes.push_back(current_box);
    cursor_y += box_height;
}

std::vector<Box> Layout::get_boxes()
{
    return boxes;
}

int Layout::get_max_width()
{
    int width = 0;

    for (auto box : boxes)
    {
        if (box.get_width() > width)
            width = box.get_width();
    }
    
    return width;
}

int Layout::get_max_height()
{
    int height = 0;

    for (auto box : boxes)
    {
        if (box.get_coordinates().at(1) + box.get_height() > height)
            height = box.get_coordinates().at(1) + box.get_height();
    }

    return height;
}

void Layout::update()
{
    construct_from_document(document);

    auto center = view.getCenter();
    auto size = view.getSize();
    sf::FloatRect view_bounds(center.x - (size.x / 2), center.y - (size.y / 2),
            size.x, size.y);

    for (auto& box : boxes)
    {
        auto coordinates = box.get_coordinates();
        box.set_visible(view_bounds.intersects(sf::FloatRect(coordinates.at(0), 
                        coordinates.at(1), box.get_width(), box.get_height())));
    }
}

void Layout::set_view(sf::View new_view)
{
    view = new_view;
}
