#ifndef LAYOUT_H
#define LAYOUT_H

#include <string>
#include <vector>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/View.hpp>

#include "../Document/Document.hpp"
#include "Box.hpp"

class Layout
{
    public:
        Layout();
        void set_width(int new_width);
        void construct_from_document(Document doc);
        void add_string(std::wstring string);
        std::vector<Box> get_boxes();
        int get_max_width();
        int get_max_height();
        void update();
        void set_view(sf::View new_view);

    protected:
        int cursor_x;
        int cursor_y;
        int width;
        std::vector<Box> boxes;
        sf::Font font;
        sf::Text text;
        bool is_font_set;
        bool is_last_box_finalized;
        sf::View view;
        Document document;
        int get_word_height(const std::wstring& word);
        int get_word_length(const std::wstring& word);
};

#endif
