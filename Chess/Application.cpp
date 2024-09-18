#include <SFML/Graphics.hpp>
#include "Game.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "Chess");
    Game game = Game();
    sf::RectangleShape bg = sf::RectangleShape(sf::Vector2f(800, 800));
    bg.setFillColor(sf::Color::Blue);
    bg.setPosition(0, 0);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:
                switch (event.key.scancode) {
                case sf::Keyboard::Scan::Escape:
                    window.close();
                    break;
                }
            }
        }

        window.clear();
        // render here
        window.draw(bg);
        game.drawBoard(window);
        window.display();
    }

    return 0;
}