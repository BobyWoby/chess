#pragma once
#include "Piece.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <iostream>
#include <array>


class Game
{
private:
	sf::RectangleShape whiteSquare, blackSquare;
	//std::map<int, Piece> pieces;
	Piece pieces[32];
public:
	float width = 400, height = 400, s_width = width / 6, offset = 120;
	Game() {
		whiteSquare = sf::RectangleShape(sf::Vector2f(s_width, s_width));
		whiteSquare.setFillColor(sf::Color::White);
		whiteSquare.setPosition(offset, offset);

		blackSquare = sf::RectangleShape(sf::Vector2f(s_width, s_width));
		whiteSquare.setFillColor(sf::Color(30, 30, 30, 255));
		whiteSquare.setPosition(offset, offset);

		resetBoard();
	}
	void resetBoard() {
		pieces[0] = Piece(ROOK, BLACK, sf::Vector2i(0, 0));
		pieces[1] = Piece(KNIGHT, BLACK, sf::Vector2i(1, 0));
		pieces[2] = Piece(BISHOP, BLACK, sf::Vector2i(2, 0));
		pieces[3] = Piece(QUEEN, BLACK, sf::Vector2i(3, 0));
		pieces[4] = Piece(KING, BLACK, sf::Vector2i(4, 0));
		pieces[5] = Piece(BISHOP, BLACK, sf::Vector2i(5, 0));
		pieces[6] = Piece(KNIGHT, BLACK, sf::Vector2i(6, 0));
		pieces[7] = Piece(ROOK, BLACK, sf::Vector2i(7, 0));
		for (int i = 0; i < 8; i++) {
			pieces[i + 8] = Piece(PAWN, BLACK, sf::Vector2i(i, 1));
		}
		pieces[16] = Piece(ROOK, WHITE, sf::Vector2i(0, 7));
		pieces[17] = Piece(KNIGHT, WHITE, sf::Vector2i(1, 7));
		pieces[18] = Piece(BISHOP, WHITE, sf::Vector2i(2, 7));
		pieces[19] = Piece(QUEEN, WHITE, sf::Vector2i(3, 7));
		pieces[20] = Piece(KING, WHITE, sf::Vector2i(4, 7));
		pieces[21] = Piece(BISHOP, WHITE, sf::Vector2i(5, 7));
		pieces[22] = Piece(KNIGHT, WHITE, sf::Vector2i(6, 7));
		pieces[23] = Piece(ROOK, WHITE, sf::Vector2i(7, 7));
		for (int i = 0; i < 8; i++) {
			pieces[i + 24] = Piece(PAWN, WHITE, sf::Vector2i(i, 6));
		}
	}

	void drawBoard(sf::RenderWindow& window) {
		// render the board
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

			}
		}

		// render the pieces
		for (auto piece : pieces) {
			piece.render(window);
		}
	}
};

