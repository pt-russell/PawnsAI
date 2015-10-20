#include "Move.h"

// CONSTRUCTORS

Move::Move(const Square& squareFrom, const Square& squareTo, bool whiteMove)
{
	from = squareFrom;
	to = squareTo;
	isWhite = whiteMove;

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			coefficients[i][j] = 0;
		}
	}
}

Move::Move()
{
}

Move::Move(const Move& foo)
{
	from = foo.from;
	to = foo.to;
	isWhite = foo.isWhite;

	// Can probably just do coefficients = foo.coefficients

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			coefficients[i][j] = foo.coefficients[i][j];
		}
	}
}

// DESTRUCTOR

Move::~Move()
{
}

// ASSIGNMENT OPERATOR

const Move& Move::operator=(const Move& foo)
{
	from = foo.from;
	to = foo.to;
	isWhite = foo.isWhite;

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			coefficients[i][j] = foo.coefficients[i][j];
		}
	}

	return *this;
}

// FRIENDS

ostream& operator<< (ostream& os, const Move& move)
{
	os << "From: " << move.GetFrom();
	os << "To: " << move.GetTo();

	if (move.IsWhite())
	{
		os << "Side: White\n";
	}

	else
	{
		os << "Side: Black\n";
	}

	/*
	for (int i = 0; i < 8; i++)
	{
		os << "Coefficients for rank " << i << ":";

		for (int j = 0; j < 8; j++)
		{
			os << " " << move.GetCoefficient(j, i);
		}

		os << "\n";
	}
	*/

	return os;
}

// GETTERS

const Square& Move::GetFrom() const
{
	return from;
}

const Square& Move::GetTo() const
{
	return to;
}

bool Move::IsWhite() const
{
	return isWhite;
}

double Move::GetCoefficient(int x, int y) const
{
	return coefficients[x][y];
}

// SETTERS

void Move::AddToCoefficient(int x, int y, double z)
{
	coefficients[x][y] += z;
}