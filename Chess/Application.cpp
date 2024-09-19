#include <SFML/Graphics.hpp>
#include "Game.h"

void posToSquare(sf::Vector2i position, Game &game, int output[]) {
    // this returns a 2 element array pointer
    output[0] = (position.x - game.offset) / game.s_width;
    output[1] = (position.y - game.offset) / game.s_width;
}

int main()
{
    int width, height;
    width = height = 800;
    sf::RenderWindow window(sf::VideoMode(width, height), "Chess");
    Game game = Game();
    sf::RectangleShape bg = sf::RectangleShape(sf::Vector2f(width, height));
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
                break;
            case sf::Event::MouseButtonPressed:
                /*sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                std::cout << mousePos.x << ", " << mousePos.y << std::endl;
                int square[2];
                posToSquare(mousePos, game, square);
                std::cout << "Square: " << square[0] << ", " << square[1] << std::endl;*/
                game.movePiece(W_PAWN, sf::Vector2i(4, 6), sf::Vector2i(4, 5));
                //game.pieces[W_PAWN]
                break;
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