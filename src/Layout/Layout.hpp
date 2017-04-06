#ifndef LAYOUT_H
#define LAYOUT_H

#include <string>
#include <vector>
#include <SFML/Graphics/Text.hpp>

#include "Box.hpp"

class Layout
{
    public:
        Layout();
        void set_width(int new_width);
        void add_string(std::wstring string);
        std::vector<Box> get_boxes();

    protected:
        int cursor_x;
        int cursor_y;
        int width;
        std::vector<Box> boxes;
        sf::Font font;
        sf::Text text;
        bool is_font_set;
};

#endif
