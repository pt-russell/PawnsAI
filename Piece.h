#ifndef PIECE_H
#define PIECE_H

#include "Square.h"

class Piece
{
private :

	bool isWhite;
	bool onBoard;
	Square square;

public :

	// Constructors, assignment operator
	Piece(bool, const Square&);
	Piece();
	Piece(const Piece&);
	~Piece();
	const Piece& operator=(const Piece&);

	// Getters
	bool IsWhite() const;
	bool IsOnBoard() const;
	const Square& GetSquare() const;

	// Setters
	void SetSquare(const Square&);
	void SetOnBoard(bool);
};

#endif
