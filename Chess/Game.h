#pragma once
#include "Piece.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <iostream>
#include <map>

enum pieceId {
	B_QUEEN, B_KING, B_ROOK, B_KNIGHT, B_BISHOP, B_PAWN,
	W_QUEEN, W_KING, W_ROOK, W_KNIGHT, W_BISHOP, W_PAWN,
};
class Game
{
private:
	sf::RectangleShape whiteSquare, blackSquare;
	sf::Sprite pieceSprites[12];
	sf::Texture *pieceTextures[12];
public:
	uint64_t pieces[12];
	uint64_t blackPieces = 0, whitePieces = 0, allPieces = 0;
	float s_width = 64, offset = (800 - s_width * 8) / 2;
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
	~Game() {
		for (int i = 0; i < 12; i++) {
			delete pieceTextures[i];
		}
	}
	void resetBoard() {
		pieces[W_PAWN]   = 0b0000000011111111000000000000000000000000000000000000000000000000;
		pieces[W_BISHOP] = 0b0010010000000000000000000000000000000000000000000000000000000000;
		pieces[W_KNIGHT] = 0b0100001000000000000000000000000000000000000000000000000000000000;
		pieces[W_ROOK]   = 0b1000000100000000000000000000000000000000000000000000000000000000;
		pieces[W_QUEEN]  = 0b0000100000000000000000000000000000000000000000000000000000000000;
		pieces[W_KING]   = 0b0001000000000000000000000000000000000000000000000000000000000000;
		
		pieces[B_PAWN]   = 0b0000000000000000000000000000000000000000000000001111111100000000;
		pieces[B_BISHOP] = 0b0000000000000000000000000000000000000000000000000000000000100100;
		pieces[B_KNIGHT] = 0b0000000000000000000000000000000000000000000000000000000001000010;
		pieces[B_ROOK]   = 0b0000000000000000000000000000000000000000000000000000000010000001;
		pieces[B_QUEEN]  = 0b0000000000000000000000000000000000000000000000000000000000001000;
		pieces[B_KING]   = 0b0000000000000000000000000000000000000000000000000000000000010000;
		for (int i = 0; i < 6; i++) {
			blackPieces = blackPieces | pieces[i];
		}
		for (int i = 6; i < 12; i++) {
			whitePieces = whitePieces | pieces[i];
		}

	}
	uint64_t posToBinary(int pos[]) {
		int digit = pos[0] + pos[1] * 8;
		return (uint64_t)1 << (digit);
	}
	void drawPiece(sf::RenderWindow& window, uint64_t bitboard, int pieceIndex) {
		int digit = 0;
		for (uint64_t i = bitboard; i != 0; i /= 2) {
			if (i & 0x1) {
				pieceSprites[pieceIndex].setPosition(sf::Vector2f((digit % 8) * s_width + offset, (int)(digit / 8) * s_width + offset));
				window.draw(pieceSprites[pieceIndex]);
			}
			digit++;
		}
	}
	void updateBbs(int pieceIndex, uint64_t mask) {
		if (pieceIndex < 6) {
			blackPieces = blackPieces ^ mask;
		}
		else {
			whitePieces = whitePieces ^ mask;
		}
	}
	void movePiece(int pieceIndex, sf::Vector2i piecePos, sf::Vector2i newPos) {
		int pPos[2] = { piecePos.x, piecePos.y };
		int nPos[2] = { newPos.x, newPos.y };
		uint64_t mask1 = posToBinary(nPos);
		uint64_t mask2 = posToBinary(pPos);
		uint64_t maskFinal = mask1 | mask2;
		pieces[pieceIndex] = pieces[pieceIndex] ^ maskFinal;
		updateBbs(pieceIndex, maskFinal);
	}
	void movePiece(int pieceIndex, int piecePos[], int newPos[]) {
		uint64_t mask1 = posToBinary(piecePos);
		uint64_t mask2 = posToBinary(newPos);
		uint64_t maskFinal = mask1 | mask2;
		pieces[pieceIndex] = pieces[pieceIndex] ^ maskFinal;
		updateBbs(pieceIndex, maskFinal);
	}
	void movePiece(int pieceIndex, uint64_t piecePos, uint64_t newPos) {
		uint64_t maskFinal = piecePos | newPos;
		pieces[pieceIndex] = pieces[pieceIndex] ^ maskFinal;
		updateBbs(pieceIndex, maskFinal);
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
		for (int i = 0; i < 12; i++) {
			drawPiece(window, pieces[i], i);
		}
	}
};

