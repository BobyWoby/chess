#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "Chess");
    
    

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

        window.display();
    }

    return 0;
}