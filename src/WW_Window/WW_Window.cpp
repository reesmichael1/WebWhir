#include <iostream>

#include "WW_Window.hpp"

WW_Window::WW_Window(int w, int h)
{
    create(sf::VideoMode(w, h), "WebWhir");

    if (!font.loadFromFile("/usr/share/fonts/TTF/DejaVuSerif.ttf"))
        std::cerr << "Error: Could not load font" << std::endl;
}

void WW_Window::show_layout()
{
    for (const auto& drawable : drawables)
        draw(drawable);
}

void WW_Window::load_from_layout(const Layout &layout)
{
    sf::Text text;
    drawables = {};

    for (auto& box : layout.get_boxes())
    {
        if (box.is_visible())
        {
            text.setFont(font);
            text.setCharacterSize(14);
            text.setFillColor(sf::Color::Black);
            text.setString(box.get_box_string());

            auto coordinates = box.get_coordinates();

            text.setPosition(coordinates.at(0), coordinates.at(1));

            drawables.push_back(text);
        }
    }

    return;
}
