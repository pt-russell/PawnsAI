#ifndef BOARD_H
#define BOARD_H

#include "Move.h"

class Board
{
private :

	// For squares, first coordinate is file. Second coordinate is rank.
	Square squares[8][8];
	Piece whitePieces[8];
	Piece blackPieces[8];
	bool isWhiteTurn;
	double materialFactor;

public :

	// Constructors, assignment operator
	Board();
	Board(const Board&);
	~Board();
	const Board& operator=(const Board&);

	// Friends

	friend ostream& operator<< (ostream&, const Board&);

	// Getters
	Piece GetWhitePiece(int) const;
	Piece GetBlackPiece(int) const;
	double GetMaterialFactor() const;

	// Validity check for a move
	bool IsMoveValid(const Move&) const;

	// Gets whose turn it is
	bool IsWhiteTurn() const;

	// Figures out move valuation
	double ValuateMove(const Move&) const;

	// Execute a move
	int ExecuteMove(const Move&);

	// Reset board
	void ResetBoard();

	// Add a value to materialFactor
	void AddToMaterialFactor(double);
};

#endif
