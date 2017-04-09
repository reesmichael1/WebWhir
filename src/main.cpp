#include <string>

#include "WW_Window/WW_Window.hpp"
#include "Document/Document.hpp"
#include "HTMLParser/HTMLParser.hpp"

#define WINDOW_WIDTH 500
#define WINDOW_HEIGHT 500

int main()
{
    std::wstring html(L"<!DOCTYPE html><html><head></head><body>"
        "<p>Hello world!</p>"
        "<p>This is a simple test HTML string that demonstrates "
        "WebWhir's rendering capabilities.</p>"
        "<p>Although work is still in the early stages, this example "
        "shows the foundation of the progress to come.");

    WW_Window window(WINDOW_WIDTH, WINDOW_HEIGHT);

    Layout layout;
    layout.set_width(WINDOW_WIDTH);

    HTMLParser parser;

    Document document = parser.construct_document_from_string(html);
    layout.construct_from_document(document);
    window.load_from_layout(layout);

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::Closed:
                {
                    window.close();
                    break;
                }

                case sf::Event::KeyPressed:
                {
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                        window.close();
                    break;
                }

                case sf::Event::Resized:
                {
                    sf::Vector2f size = static_cast<sf::Vector2f>(window.getSize());
                    sf::View newView(sf::FloatRect(0.f, 0.f, size.x, size.y));
                    window.setView(newView);

                    layout.set_width(size.x);
                    layout.construct_from_document(document);
                    window.load_from_layout(layout);

                    break;
                }

                default:
                    break;
            }
        }

        window.clear(sf::Color::White);
        window.show_layout();
        window.display();
    }
}
