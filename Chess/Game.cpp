#include "Game.h"

void Game::resetBoard() {
	whitePieces = blackPieces = 0;
	pieces[W_PAWN] = 0b0000000011111111000000000000000000000000000000000000000000000000;
	pieces[W_BISHOP] = 0b0010010000000000000000000000000000000000000000000000000000000000;
	pieces[W_KNIGHT] = 0b0100001000000000000000000000000000000000000000000000000000000000;
	pieces[W_ROOK] = 0b1000000100000000000000000000000000000000000000000000000000000000; 
	pieces[W_QUEEN] = 0b0000100000000000000000000000000000000000000000000000000000000000;
	pieces[W_KING] = 0b0001000000000000000000000000000000000000000000000000000000000000;

	pieces[B_PAWN] = 0b0000000000000000000000000000000000000000000000001111111100000000;
	pieces[B_BISHOP] = 0b0000000000000000000000000000000000000000000000000000000000100100;
	pieces[B_KNIGHT] = 0b0000000000000000000000000000000000000000000000000000000001000010;
	pieces[B_ROOK] = 0b0000000000000000000000000000000000000000000000000000000010000001;
	pieces[B_QUEEN] = 0b0000000000000000000000000000000000000000000000000000000000001000;
	pieces[B_KING] = 0b0000000000000000000000000000000000000000000000000000000000010000;
	for (int i = 0; i < 6; i++) {
		blackPieces = blackPieces | pieces[i];
	}
	for (int i = 6; i < 12; i++) {
		whitePieces = whitePieces | pieces[i];
	}
}

uint64_t Game::posToBinary(int pos[]) {
	int digit = pos[0] + pos[1] * 8;
	return (uint64_t)1 << (digit);
}
void Game::binToPos(uint64_t input, int output[2]) {
	int digit = 0;
	for (uint64_t i = input; i != 0; i /= 2) {
		if (i & 0x1) break;
		digit++;
	}
	output[0] = digit / 8;
	output[1] = digit % 8;
}

bool Game::checkBishop(uint64_t move, uint64_t piece)
{
	uint64_t tmp = piece;
	bool valid = true;
	while (tmp != 0 && valid) {
		tmp = tmp >> 7;
		if (tmp & whitePieces || tmp & blackPieces) valid = false;
		if (tmp & move) return true;
	}
	tmp = piece;
	valid = true;
	while (tmp != 0 && valid) {
		tmp = tmp >> 9;
		if (tmp & whitePieces || tmp & blackPieces) valid = false;
		if (tmp & move) return true;
	}
	tmp = piece;
	valid = true;
	while (tmp != 0 && valid) {
		tmp = tmp << 7;
		if (tmp & whitePieces || tmp & blackPieces) valid = false;
		if (tmp & move) return true;
	}
	tmp = piece;
	valid = true;
	while (tmp != 0 && valid) {
		tmp = tmp << 9;
		if (tmp & whitePieces || tmp & blackPieces) valid = false;
		if (tmp & move) return true;
	}
	return false;
}

bool Game::checkKnight(uint64_t move, uint64_t piece)
{
	uint64_t tmp = piece;
	//if()
	return false;
}

bool Game::isLegalMove(int pieceId, uint64_t inputMove, uint64_t inputPiece)
{
	int mvArr[2], pArr[2];
	binToPos(inputMove, mvArr);
	binToPos(inputPiece, pArr);
	if (pieceId > 5) {
		//piece is white
		if (inputMove & whitePieces) return false; // make sure the piece isn't trying to take a piece of the same color
	}
	else {
		if (inputMove & blackPieces) return false; // make sure the piece isn't trying to take a piece of the same color
	}
	switch (pieceId) {
	case B_PAWN:
		break;
	case W_PAWN:
		break;
	case B_BISHOP:
		return checkBishop(inputMove, inputPiece);
		break;
	case W_BISHOP:
		return checkBishop(inputMove, inputPiece);
	}
	return true;
}

void Game::drawPiece(sf::RenderWindow& window, uint64_t bitboard, int pieceIndex) {
	int digit = 0;
	for (uint64_t i = bitboard; i != 0; i /= 2) {
		if (i & 0x1) {
			pieceSprites[pieceIndex].setPosition(sf::Vector2f((digit % 8) * s_width + offset, (int)(digit / 8) * s_width + offset));
			window.draw(pieceSprites[pieceIndex]);
		}
		digit++;
	}
}

void Game::updateBbs(int pieceIndex, uint64_t mask) {
	pieces[pieceIndex] = pieces[pieceIndex] ^ mask;
	if (pieceIndex < 6) {
		blackPieces = blackPieces ^ mask;
	}
	else {
		whitePieces = whitePieces ^ mask;
	}
}

void Game::movePiece(int pieceIndex, sf::Vector2i piecePos, sf::Vector2i newPos) {
	int pPos[2] = { piecePos.x, piecePos.y };
	int nPos[2] = { newPos.x, newPos.y };
	uint64_t mask1 = posToBinary(nPos);
	uint64_t mask2 = posToBinary(pPos);
	uint64_t maskFinal = mask1 | mask2;
	updateBbs(pieceIndex, maskFinal);
}

void Game::movePiece(int pieceIndex, int piecePos[], int newPos[]) {
	uint64_t mask1 = posToBinary(piecePos);
	uint64_t mask2 = posToBinary(newPos);
	uint64_t maskFinal = mask1 | mask2;
	updateBbs(pieceIndex, maskFinal);
}

void Game::movePiece(int pieceIndex, uint64_t piecePos, uint64_t newPos) {
	uint64_t maskFinal = piecePos | newPos;
	updateBbs(pieceIndex, maskFinal);
}

void Game::drawBoard(sf::RenderWindow& window) {
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