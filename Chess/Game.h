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
	sf::Sprite pieceSprites[12];
	sf::Texture *pieceTextures[12];
	uint64_t wp, bp, wb, bb, wKn, bKn, wr, br, wq, bq, wK, bK;
public:
	float width = 400, height = 400, s_width = width / 6, offset = 120;
	Game() {
		whiteSquare = sf::RectangleShape(sf::Vector2f(s_width, s_width));
		whiteSquare.setFillColor(sf::Color::White);
		whiteSquare.setPosition(offset, offset);

		blackSquare = sf::RectangleShape(sf::Vector2f(s_width, s_width));
		whiteSquare.setFillColor(sf::Color(30, 30, 30, 255));
		whiteSquare.setPosition(offset, offset);
		for (int i = 0; i < 12; i++) {
			pieceTextures[i] = new sf::Texture();
			pieceTextures[i]->loadFromFile("./res/ChessPiecesArray.png");
			pieceSprites[i].setTexture(*pieceTextures[i]);
			pieceSprites[i].setTextureRect(sf::IntRect(i % 6 * 60, (i > 5) * 60, 60, 60));
			pieceSprites[i].setScale(s_width / 60, s_width / 60);
		}
		resetBoard();
	}
	void resetBoard() {
		wp = 0b0000000011111111000000000000000000000000000000000000000000000000;
		wb = 0b0010010000000000000000000000000000000000000000000000000000000000;
		wKn= 0b0100001000000000000000000000000000000000000000000000000000000000;
		wr = 0b1000000100000000000000000000000000000000000000000000000000000000;
		wq = 0b0001000000000000000000000000000000000000000000000000000000000000;
		wK = 0b0000100000000000000000000000000000000000000000000000000000000000;
		bp = 0b0000000000000000000000000000000000000000000000001111111100000000;
		bb = 0b0000000000000000000000000000000000000000000000000010010000000000;
		bK = 0b0000000000000000000000000000000000000000000000000001000000000000;
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
		int digit = 0;
		for (uint64_t i = wp; i != 0; i /= 2) {
			if (i & 0x1) {
				pieceSprites[11].setPosition(sf::Vector2f((digit % 8) * s_width + offset, (int)(digit / 8) * s_width + offset));
				window.draw(pieceSprites[11]);
			}
			digit++;
		}
		digit = 0;
		for (uint64_t i = wb; i != 0; i /= 2) {
			if (i & 0x1) {
				pieceSprites[10].setPosition(sf::Vector2f((digit % 8) * s_width + offset, (int)(digit / 8) * s_width + offset));
				window.draw(pieceSprites[10]);
			}
			digit++;
		}
		digit = 0;
		for (uint64_t i = wKn; i != 0; i /= 2) {
			if (i & 0x1) {
				pieceSprites[9].setPosition(sf::Vector2f((digit % 8) * s_width + offset, (int)(digit / 8) * s_width + offset));
				window.draw(pieceSprites[9]);
			}
			digit++;
		}
		digit = 0;
		for (uint64_t i = wr; i != 0; i /= 2) {
			if (i & 0x1) {
				pieceSprites[8].setPosition(sf::Vector2f((digit % 8) * s_width + offset, (int)(digit / 8) * s_width + offset));
				window.draw(pieceSprites[8]);
			}
			digit++;
		}
		digit = 0;
		for (uint64_t i = wK; i != 0; i /= 2) {
			if (i & 0x1) {
				pieceSprites[7].setPosition(sf::Vector2f((digit % 8) * s_width + offset, (int)(digit / 8) * s_width + offset));
				window.draw(pieceSprites[7]);
			}
			digit++;
		}
		digit = 0;
		for (uint64_t i = wq; i != 0; i /= 2) {
			if (i & 0x1) {
				pieceSprites[6].setPosition(sf::Vector2f((digit % 8) * s_width + offset, (int)(digit / 8) * s_width + offset));
				window.draw(pieceSprites[6]);
			}
			digit++;
		}
	}
};

