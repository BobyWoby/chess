#pragma once
#include <SFML/Graphics.hpp>
enum PieceType{
	PAWN, BISHOP, KNIGHT, ROOK, QUEEN, KING
};
class Piece
{
private:
	bool isWhite;
	sf::Vector2i pos;
	PieceType type;
};

