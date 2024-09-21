#include <SFML/Graphics.hpp>
#include "Game.h"

bool posToSquare(sf::Vector2i position, Game &game, int output[]) {
    // this returns a 2 element array pointer
    output[0] = (position.x - game.offset) / game.s_width;
    output[1] = (position.y - game.offset) / game.s_width;
    //if(output[0] >= 0 && output[0] <8)
    return (output[0] >= 0 && output[0] < 8 && output[1] >= 0 && output[1] < 8);
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
    
    bool clickedPiece = false, mvmtBuffer = false;
    uint64_t pieceBuffer = 0;
    int pieceIdBuffer = 0;

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
                case sf::Keyboard::Scan::R:
                    game.resetBoard();
                    break;
                }
                break;
            case sf::Event::MouseButtonPressed:
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                int square[2];
                if (posToSquare(mousePos, game, square)) {
                    if (clickedPiece) {
                        uint64_t pos2 = game.posToBinary(square);
                        if (game.isLegalMove(pieceIdBuffer, pos2, pieceBuffer)) {

                            // check if the piece overlaps with another piece, if it does, remove that piece
                            for (int i = 0; i < 12; i++) {
                                if (i == pieceIdBuffer) {continue;}
                                if (pos2 & game.pieces[i]) {
                                    game.updateBbs(i, pos2);
                                }
                            }

                            if (!(game.pieces[pieceIdBuffer] & pos2)) game.movePiece(pieceIdBuffer, pieceBuffer, pos2);
                            mvmtBuffer = true;
                            clickedPiece = false;
                        }
                        else {
                            mvmtBuffer = true;
                            clickedPiece = false;
                        }
                    }
                    for (int i = 0; i < 12; i++) {
                        if (game.posToBinary(square) & game.pieces[i]) {
                            if(!mvmtBuffer && !clickedPiece){
                                clickedPiece = true;
                                pieceBuffer = game.posToBinary(square);
                                pieceIdBuffer = i;
                            }
                            else if(!clickedPiece) {
                                mvmtBuffer = false;
                            }
                            
                        }
                    }
                }
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