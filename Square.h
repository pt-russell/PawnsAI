#ifndef SQUARE_H
#define SQUARE_H

#include <iostream>

using namespace std;

class Square
{
private :

	int file;
	int rank;

public :

	// Constructors, assignment operator
	Square(int, int);
	Square();
	Square(const Square&);
	~Square();
	const Square& operator=(const Square&);

	// Friends
	friend ostream& operator<< (ostream&, const Square&);

	// Relational operators
	bool operator==(const Square&) const;

	// Getters
	int GetFile() const;
	int GetRank() const;
};

#endif