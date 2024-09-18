#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

enum PieceType{
	NULL_TYPE = 0, PAWN = 1, BISHOP, KNIGHT, ROOK, QUEEN, KING
};
enum PieceColor {
	BLACK = 0, WHITE = 1
};
class Piece
{
private:
	PieceColor color;
	sf::Texture *texture;
	int texX, texY;
public:
	PieceType type;
	sf::Sprite sprite;
	Piece() {
		color = BLACK;
		type = NULL_TYPE;
	}
	Piece(PieceType t, PieceColor c) : type(t), color(c){
		int x = 0;
		int y = color * 60;
		switch (t) {
		case PAWN:
			x = 5 * 60;	
			break;
		case BISHOP:
			x = 4 * 60;	
			break;
		case KNIGHT:
			x = 3 * 60;	
			break;
		case ROOK:
			x = 2 * 60;	
			break;
		case QUEEN:
			x = 0 * 60;	
			break;
		case KING:
			x = 1 * 60;	
			break;
		default:
			x = 0;
			break;
		}
		texX = x, texY = y;
		texture = new sf::Texture;
		texture->loadFromFile("./res/ChessPiecesArray.png");
		sprite.setTexture(*texture);
		sprite.setTextureRect(sf::IntRect(texX, texY, 60, 60));
	}

	void render(sf::RenderWindow& window) {
		window.draw(sprite);
	}

};

