#pragma once
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

	bool checkBishop(uint64_t move, uint64_t piece);
	bool checkKnight(uint64_t move, uint64_t piece);

public:
	uint64_t pieces[12];
	uint64_t blackPieces = 0, whitePieces = 0, allPieces = 0;
	float s_width = 64, offset = (800 - s_width * 8) / 2;
	bool whitesTurn = true;
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

	uint64_t posToBinary(int pos[]);
	void binToPos(uint64_t input, int output[]);
	bool isLegalMove(int pieceId, uint64_t inputMove, uint64_t inputPiece);

	void movePiece(int pieceIndex, sf::Vector2i piecePos, sf::Vector2i newPos);
	void movePiece(int pieceIndex, int piecePos[], int newPos[]);
	void movePiece(int pieceIndex, uint64_t piecePos, uint64_t newPos);
	void updateBbs(int pieceIndex, uint64_t mask);


	void resetBoard();
	void drawPiece(sf::RenderWindow& window, uint64_t bitboard, int pieceIndex);
	void drawBoard(sf::RenderWindow& window);
	
};

