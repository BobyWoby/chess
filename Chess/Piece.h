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
	float width = 400, height = 400, s_width = width / 6, offset = 120;
	PieceColor color;
	sf::Texture *texture;
	int texX, texY;
	
public:

	sf::Vector2i position;
	PieceType type;
	sf::Sprite sprite;

	Piece() {
		color = BLACK;
		type = NULL_TYPE;
	}
	Piece(PieceType t, PieceColor c, sf::Vector2i pos) : type(t), color(c), position(pos){
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
		sprite.setScale(s_width / 60, s_width / 60);
		sprite.setPosition(sf::Vector2f(pos.x * s_width + offset, pos.y * s_width + offset));
	}
	void move(sf::Vector2i mvmtVec) {
		position += mvmtVec;
		sprite.setPosition(sf::Vector2f(position.x * s_width + offset, position.y * s_width + offset));
	}
	void render(sf::RenderWindow& window) {
		window.draw(sprite);
	}

};

