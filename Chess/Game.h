#pragma once
#include "Piece.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <iostream>
#include <array>


class Game
{
private:
	float width = 400, height = 400, s_width = width / 6, offset = 120;
	sf::RectangleShape whiteSquare, blackSquare;
	std::map<int, Piece> pieces;
public:
	Game() {
		whiteSquare = sf::RectangleShape(sf::Vector2f(s_width, s_width));
		whiteSquare.setFillColor(sf::Color::White);
		whiteSquare.setPosition(offset, offset);

		blackSquare = sf::RectangleShape(sf::Vector2f(s_width, s_width));
		whiteSquare.setFillColor(sf::Color(30, 30, 30, 255));
		whiteSquare.setPosition(offset, offset);
		pieces[0x00] = Piece(QUEEN, BLACK);


		std::map<int, Piece>::iterator it = pieces.begin();
		while (it != pieces.end()) {
			it->second.sprite.setScale(s_width / 60, s_width / 60);
			it->second.sprite.setPosition(offset, offset);

		}
	}
	void drawBoard(sf::RenderWindow& window) {
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if ((i + j) % 2 == 0)
				{
					window.draw(whiteSquare);
					whiteSquare.setPosition(s_width * i + offset, s_width * j + offset);
				}
				else {
					window.draw(blackSquare);
					blackSquare.setPosition(s_width * i + offset, s_width * j + offset);
				}
				
				if (pieces.find(j * 16 + i) != pieces.end()) {
					pieces[j * 16 + i].render(window);
				}
			}
		}
		
	}
};

