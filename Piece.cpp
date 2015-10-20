#include "Piece.h"

// CONSTRUCTORS

Piece::Piece(bool isPieceWhite, const Square& whereIsPiece)
{
	isWhite = isPieceWhite;
	square = whereIsPiece;
	onBoard= true;
}

Piece::Piece()
{
	isWhite = true;
	onBoard= true;
}

Piece::Piece(const Piece& foo)
{
	isWhite = foo.isWhite;
	square = foo.GetSquare();
	onBoard= true;
}

// DESTRUCTOR

Piece::~Piece()
{
}

// ASSIGNMENT OPERATOR

const Piece& Piece::operator=(const Piece& foo)
{
	isWhite = foo.isWhite;
	square = foo.GetSquare();
	return *this;
}

// GETTERS

bool Piece::IsWhite() const
{
	return isWhite;
}

bool Piece::IsOnBoard() const
{
	return onBoard;
}

const Square& Piece::GetSquare() const
{
	return square;
}

// SETTERS

void Piece::SetSquare(const Square& newSquare)
{
	square = newSquare;
}

void Piece::SetOnBoard(bool x)
{
	onBoard = x;
}
