#include "Game.h"

void Game::resetBoard() {
	whitePieces = blackPieces = 0;
	//pieces[W_PAWN] = 0b0000000011111111000000000000000000000000000000000000000000000000;
	//pieces[W_BISHOP] = 0b0010010000000000000000000000000000000000000000000000000000000000;
	//pieces[W_KNIGHT] = 0b0100001000000000000000000000000000000000000000000000000000000000;
	//pieces[W_ROOK] = 0b1000000100000000000000000000000000000000000000000000000000000000; 
	pieces[W_QUEEN] = 0b0000100000000000000000000000000000000000000000000000000000000000;
	//pieces[W_KING] = 0b0001000000000000000000000000000000000000000000000000000000000000;

	//pieces[B_PAWN] = 0b0000000000000000000000000000000000000000000000001111111100000000;
	//pieces[B_BISHOP] = 0b0000000000000000000000000000000000000000000000000000000000100100;
	//pieces[B_KNIGHT] = 0b0000000000000000000000000000000000000000000000000000000001000010;
	//pieces[B_ROOK] = 0b0000000000000000000000000000000000000000000000000000000010000001;
	pieces[B_QUEEN] = 0b0000000000000000000000000000000000000000000000000000000000001000;
	//pieces[B_KING] = 0b0000000000000000000000000000000000000000000000000000000000010000;
	for (int i = 0; i < 6; i++) {
		blackPieces = blackPieces | pieces[i];
	}
	for (int i = 6; i < 12; i++) {
		whitePieces = whitePieces | pieces[i];
	}
	whitesTurn = true;
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
	//TODO: maybe try Move Rays, cuz i dont think this is gonna work, tho there is probably a way to make it work

	uint64_t tmp = piece;
	bool valid = true;
	while (tmp != 0 && valid) {
		tmp >>= 7;
		if (tmp & whitePieces || tmp & blackPieces) valid = false;
		if (tmp & move) return true;
	}
	tmp = piece;
	valid = true;
	while (tmp != 0 && valid) {
		tmp >>= 9;
		if (tmp & whitePieces || tmp & blackPieces) valid = false;
		if (tmp & move) return true;
	}
	tmp = piece;
	valid = true;
	while (tmp != 0 && valid) {
		tmp <<= 7;
		if (tmp & whitePieces || tmp & blackPieces) valid = false;
		if (tmp & move) return true;
	}
	tmp = piece;
	valid = true;
	while (tmp != 0 && valid) {
		tmp <<= 9;
		if (tmp & whitePieces || tmp & blackPieces) valid = false;
		if (tmp & move) return true;
	}
	return false;
}

bool Game::checkKnight(uint64_t move, uint64_t piece)
{
	if ((piece << 6) & move) return true;
	if ((piece << 10) & move) return true;
	if ((piece << 15) & move) return true;
	if ((piece << 17) & move) return true;
	if ((piece >> 6) & move) return true;
	if ((piece >> 10) & move) return true;
	if ((piece >> 15) & move) return true;
	if ((piece >> 17) & move) return true;
	return false;
}
const int tab64[64] = {
	63,  0, 58,  1, 59, 47, 53,  2,
	60, 39, 48, 27, 54, 33, 42,  3,
	61, 51, 37, 40, 49, 18, 28, 20,
	55, 30, 34, 11, 43, 14, 22,  4,
	62, 57, 46, 52, 38, 26, 32, 41,
	50, 36, 17, 19, 29, 10, 13, 21,
	56, 45, 25, 31, 35, 16,  9, 12,
	44, 24, 15,  8, 23,  7,  6,  5 };

int log2_64(uint64_t value)
{
	value |= value >> 1;
	value |= value >> 2;
	value |= value >> 4;
	value |= value >> 8;
	value |= value >> 16;
	value |= value >> 32;
	return tab64[((uint64_t)((value - (value >> 1)) * 0x07EDD5E59A4E28C2)) >> 58];
}

void Game::generateNorthRay(uint64_t square, uint64_t &output) {
	if (!square)
	{
		output = 0;
		return;
	}
	int col = log2_64(square) % 8;
	int row = log2_64(square) / 8;
	output = 0;

	// generate a north-pointing ray
	for (int i = 0; i < row; i++) {
		output |= ((uint64_t)1 << col) << (i * 8);
	}
}

void Game::generateEastRay(uint64_t square, uint64_t &output) {
	if (!square)
	{
		output = 0;
		return;
	}
	int col = log2_64(square) % 8;
	int row = log2_64(square) / 8;
	output = 0;
	// generate a east-pointing ray
	for (int i = col+1; i < 8; i++) {
		output |= ((uint64_t)1 << row * 8) << i;
	}

}

void Game::generateSouthRay(uint64_t square, uint64_t &output) {
	if (!square)
	{
		output = 0;
		return;
	}
	int col = log2_64(square) % 8;
	int row = log2_64(square) / 8;
	output = 0;

	// generate a south-pointing ray
	for (int i = row+1; i < 8; i++) {
		output |= ((uint64_t)1 << col) << (i * 8);
	}
}

void Game::generateWestRay(uint64_t square, uint64_t &output) {
	if (!square)
	{
		output = 0;
		return;
	}
	int col = log2_64(square) % 8;
	int row = log2_64(square) / 8;
	output = 0;
	// generate a west-pointing ray
	for (int i = 0; i < col; i++) {
		output |= ((uint64_t)1 << row * 8) << i;
	}
}
int Game::firstBit(uint64_t number) {
	int cnt = -1;
	//if (number) while (!(number & (1 << cnt++)));
	while (number) {
		cnt++;
		number <<= 1;
	}
	if (cnt == -1) return 0;
	return cnt;
}

int Game::lastBit(uint64_t number) {
	int cnt = -1;
	while (number) {
		cnt++;
		number >>= 1;
	}
	if (cnt == -1) return 0;
	return cnt;
}

bool Game::checkRook(uint64_t move, uint64_t piece)
{
	uint64_t allPieces = whitePieces | blackPieces;

	uint64_t rays[4], moveMask = 0;
	generateNorthRay(piece, rays[0]);
	generateEastRay( piece, rays[1]);
	generateSouthRay(piece, rays[2]);
	generateWestRay( piece, rays[3]);

	uint64_t nBlocker = rays[0] & allPieces;
	nBlocker = (lastBit(nBlocker) != 0) ? (uint64_t)1 << (lastBit(nBlocker)) : 0;
	uint64_t nBlockerRay = 0;
	generateNorthRay(nBlocker, nBlockerRay);
	moveMask |= rays[0] ^ nBlockerRay;

	uint64_t eBlocker = rays[1] & allPieces;
	eBlocker = (firstBit(eBlocker) != 0) ? (uint64_t)1 << firstBit(eBlocker) : 0;
	uint64_t eBlockerRay = 0;
	generateEastRay(eBlocker, eBlockerRay);
	moveMask |= rays[1] ^ eBlockerRay;
	
	uint64_t sBlocker = rays[2] & allPieces;
	sBlocker = (firstBit(sBlocker) != 0)? (uint64_t)1 << (firstBit(sBlocker)) : 0;
	uint64_t sBlockerRay = 0;
	generateSouthRay(sBlocker, sBlockerRay);
	moveMask |= rays[2] ^ sBlockerRay;

	uint64_t wBlocker = rays[3] & allPieces;
	wBlocker = (lastBit(wBlocker) != 0) ? (uint64_t)1 << lastBit(wBlocker) : 0;
	uint64_t wBlockerRay = 0;
	generateWestRay(wBlocker, wBlockerRay);
	moveMask |= rays[3] ^ wBlockerRay;

	return (moveMask & move)? true : false;
}

bool Game::checkPawn(uint64_t move, uint64_t piece, bool isWhite)
{
	uint64_t allPieces = whitePieces | blackPieces;
	if (isWhite) {
		if (move & blackPieces) {
			// check if pawn is taking a piece
			return move & piece >> 7 || move & piece >> 9;
		}
		else if (piece & (uint64_t)0xff000000000000) {
			// on home rank
			
			return move & piece >> 8 || (move & piece >> 16 && !((piece >> 8) & (whitePieces | blackPieces)));
		}
		else {
			return move & piece >> 8;
		}
	} else {
		if (move & whitePieces) {
			// check if pawn is taking a piece
			return move & piece << 7 || move & piece << 9;
		}
		else if (piece & (uint64_t)0xff00) {
			return move & piece << 8 || (move & piece << 16 && !((piece << 8) & (whitePieces | blackPieces)));
		}
		else {
			return move & piece << 8;
		}
	}
	return false;
}

bool Game::checkKing(uint64_t move, uint64_t piece)
{
	return move & piece << 1 || 
		move & piece << 7 || 
		move & piece << 8 || 
		move & piece << 9 || 
		move & piece >> 1 || 
		move & piece >> 7 || 
		move & piece >> 8 || 
		move & piece >> 9;
}


bool Game::isLegalMove(int pieceId, uint64_t inputMove, uint64_t inputPiece)
{
	if (pieceId > 5) {
		//piece is white
		if (inputMove & whitePieces) return false; // make sure the piece isn't trying to take a piece of the same color
	}
	else {
		if (inputMove & blackPieces) return false; // make sure the piece isn't trying to take a piece of the same color
	}
	switch (pieceId) {
	case B_PAWN:
		return checkPawn(inputMove, inputPiece, false);
	case W_PAWN:
		return checkPawn(inputMove, inputPiece, true);
	case B_BISHOP:
		return checkBishop(inputMove, inputPiece);
	case W_BISHOP:
		return checkBishop(inputMove, inputPiece);
	case B_KNIGHT:
		return checkKnight(inputMove, inputPiece);
	case W_KNIGHT:
		return checkKnight(inputMove, inputPiece);
	case B_ROOK:
		return checkRook(inputMove, inputPiece);
	case W_ROOK:
		return checkRook(inputMove, inputPiece);
	case B_QUEEN:
		return checkBishop(inputMove, inputPiece) || checkRook(inputMove, inputPiece);
	case W_QUEEN:
		return checkBishop(inputMove, inputPiece) || checkRook(inputMove, inputPiece);
	case B_KING:
		return checkKing(inputMove, inputPiece);
	case W_KING:
		return checkKing(inputMove, inputPiece);
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