#ifndef MOVE_H
#define MOVE_H

#include "Piece.h"

class Move
{
private :

	Square from;
	Square to;
	bool isWhite;
	double coefficients[8][8];

public :

	// Constructors, assignment operator
	Move(const Square&, const Square&, bool);
	Move();
	Move(const Move&);
	~Move();
	const Move& operator=(const Move&);

	// Friends

	friend ostream& operator<< (ostream&, const Move&);

	// Getters
	const Square& GetFrom() const;
	const Square& GetTo() const;
	bool IsWhite() const;
	double GetCoefficient(int, int) const;

	// Add an amount to a coefficient (since we never actually set it)
	void AddToCoefficient(int, int, double);
};

#endif