#include "Square.h"

// CONSTRUCTORS

Square::Square(int horizontalCoord, int verticalCoord)
{
	file = horizontalCoord;
	rank = verticalCoord;
}

Square::Square()
{
	file = 0;
	rank = 0;
}

Square::Square(const Square& foo)
{
	file = foo.file;
	rank = foo.rank;
}

// DESTRUCTOR

Square::~Square()
{
}

// ASSIGNMENT OPERATOR

const Square& Square::operator= (const Square& foo)
{
	file = foo.file;
	rank = foo.rank;
	return *this;
}

// FRIENDS

ostream& operator<< (ostream& os, const Square& square)
{
	os << "(" << square.GetFile() << ", " << square.GetRank() << ")\n";

	return os;
}

// RELATIONAL OPERATORS

bool Square::operator== (const Square& foo) const
{
	if (file == foo.file && rank == foo.rank)
	{
		return true;
	}

	return false;
}

// GETTERS

int Square::GetFile() const
{
	return file;
}

int Square::GetRank() const
{
	return rank;
}