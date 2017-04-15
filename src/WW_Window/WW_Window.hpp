#ifndef WW_WINDOW_H
#define WW_WINDOW_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics/Text.hpp>
#include <vector>

#include "../Layout/Layout.hpp"

class WW_Window : public sf::RenderWindow
{
    public:
        WW_Window(int w, int h);
        void load_from_layout(const Layout &layout);
        void show_layout();

    protected:
        sf::Font font;
        std::vector<sf::Text> drawables;
};

#endif
