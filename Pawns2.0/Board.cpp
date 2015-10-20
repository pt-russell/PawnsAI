#include "Board.h"
#include <cmath>

// CONSTRUCTORS

Board::Board()
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			squares[i][j] = Square(i, j);
		}

		whitePieces[i] = Piece(true, squares[i][1]);
		blackPieces[i] = Piece(false, squares[i][6]);
	}
}

Board::Board(const Board& foo)
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			squares[i][j] = foo.squares[i][j];
		}

		whitePieces[i] = foo.whitePieces[i];
		blackPieces[i] = foo.blackPieces[i];

		isWhiteTurn = foo.isWhiteTurn;
	}

	materialFactor = foo.materialFactor;
}

// DESTRUCTOR

Board::~Board()
{
}

// ASSIGNMENT OPERATOR

const Board& Board::operator= (const Board& foo)
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			squares[i][j] = foo.squares[i][j];
		}

		whitePieces[i] = foo.whitePieces[i];
		blackPieces[i] = foo.blackPieces[i];

		isWhiteTurn = foo.isWhiteTurn;
	}

	materialFactor = foo.materialFactor;

	return *this;
}

// FRIENDS

ostream& operator<< (ostream& os, const Board& board)
{
	for (int i = 7; i >= 0; i--)
	{
		for (int j = 0; j < 8; j++)
		{
			for (int k = 0; k < 8; k++)
			{
				if (board.whitePieces[k].GetSquare() == Square(j, i) && board.whitePieces[k].IsOnBoard())
				{
					cout << "W";
					break;
				}

				else if (board.blackPieces[k].GetSquare() == Square(j, i) && board.blackPieces[k].IsOnBoard())
				{
					cout << "B";
					break;
				}

				if (k == 7)
				{
					cout << ".";
				}
			}

			cout << " ";
		}

		cout << "\n";
	}

	return os;
}

// GETTERS

Piece Board::GetWhitePiece(int x) const
{
	return whitePieces[x];
}

Piece Board::GetBlackPiece(int x) const
{
	return blackPieces[x];
}

double Board::GetMaterialFactor() const
{
	return materialFactor;
}

// Check if a move is valid

bool Board::IsMoveValid(const Move& move) const
{
	// Return false if the move's colour does not correspond to the player whose turn it is

	if (move.IsWhite() != isWhiteTurn)
	{
		return false;
	}

	// Return false if a piece of the move's colour is not on the source square

	bool sourceCheck = false;

	if (move.IsWhite())
	{
		for (int i = 0; i < 8; i++)
		{
			if (whitePieces[i].GetSquare() == move.GetFrom() && whitePieces[i].IsOnBoard())
			{
				sourceCheck = true;
				break;
			}
		}
	}

	else if (!move.IsWhite())
	{
		for (int i = 0; i < 8; i++)
		{
			if (blackPieces[i].GetSquare() == move.GetFrom() && blackPieces[i].IsOnBoard())
			{
				sourceCheck = true;
				break;
			}
		}
	}

	if (!sourceCheck)
	{
		return false;
	}

	// If file is not the same, check it satisfies the following:
	// 1. It's a one-square diagonal move
	// 2. There's an opposing piece on the target square

	if (move.GetFrom().GetFile() - move.GetTo().GetFile() != 0)
	{
		// First case - if the move is for a white piece
		
		if (move.IsWhite())
		{
			// If not a one-square diagonal move up the board, return false

			if (move.GetFrom().GetFile() - move.GetTo().GetFile() != 1 && move.GetFrom().GetFile() - move.GetTo().GetFile() != -1)
			{
				return false;
			}

			if (move.GetTo().GetRank() - move.GetFrom().GetRank() != 1)
			{
				return false;
			}

			// Having passed that check, if there's a black piece on the target square return true (else return false)

			for (int i = 0; i < 8; i++)
			{
				if (blackPieces[i].GetSquare() == move.GetTo() && blackPieces[i].IsOnBoard())
				{
					return true;
				}
			}

			return false;
		}

		// Same again but if the move is for a black piece

		if (!move.IsWhite())
		{
			// If not a one-square diagonal move down the board, return false

			if (move.GetFrom().GetFile() - move.GetTo().GetFile() != 1 && move.GetFrom().GetFile() - move.GetTo().GetFile() != -1)
			{
				return false;
			}

			if (move.GetFrom().GetRank() - move.GetTo().GetRank() != 1)
			{
				return false;
			}

			// Having passed that check, if there's a white piece on the target square return true (else return false)

			for (int i = 0; i < 8; i++)
			{
				if (whitePieces[i].GetSquare() == move.GetTo() && whitePieces[i].IsOnBoard())
				{
					return true;
				}
			}

			return false;
		}
	}

	// If the file is the same, check the move satisfies the following:
	// 1. It is either one or two squares in the appropriate direction (depending on whether the piece is on its starting square)
	// 2. There are no pieces in the way

	if (move.GetFrom().GetFile() == move.GetTo().GetFile())
	{
		// First case - move is for a white piece

		if (move.IsWhite())
		{
			if (move.GetTo().GetRank() - move.GetFrom().GetRank() > 2 || move.GetTo().GetRank() - move.GetFrom().GetRank() <= 0)
			{
				return false;
			}

			if (move.GetTo().GetRank() - move.GetFrom().GetRank() == 2 && move.GetFrom().GetRank() != 1)
			{
				return false;
			}

			// Now for each intermediate square, return false if there's a piece on it

			for (int i = move.GetFrom().GetRank() + 1; i <= move.GetTo().GetRank(); i++)
			{
				for (int j = 0; j < 8; j++)
				{
					if (whitePieces[j].GetSquare() == Square(move.GetFrom().GetFile(), i) && whitePieces[j].IsOnBoard())
					{
						return false;
					}

					if (blackPieces[j].GetSquare() == Square(move.GetFrom().GetFile(), i) && blackPieces[j].IsOnBoard())
					{
						return false;
					}
				}
			}

			return true;
		}

		// Same again, but if the move is for a black piece

		if (!move.IsWhite())
		{
			if (move.GetFrom().GetRank() - move.GetTo().GetRank() > 2 || move.GetFrom().GetRank() - move.GetTo().GetRank() <= 0)
			{
				return false;
			}

			if (move.GetFrom().GetRank() - move.GetTo().GetRank() == 2 && move.GetFrom().GetRank() != 6)
			{
				return false;
			}

			// Now for each intermediate square, return false if there's a piece on it

			for (int i = move.GetFrom().GetRank() - 1; i >= move.GetTo().GetRank(); i--)
			{
				for (int j = 0; j < 8; j++)
				{
					// Minor performance dip? Could avoid calling constructor and check values directly.

					if (whitePieces[j].GetSquare() == Square(move.GetFrom().GetFile(), i) && whitePieces[j].IsOnBoard())
					{
						return false;
					}

					if (blackPieces[j].GetSquare() == Square(move.GetFrom().GetFile(), i) && whitePieces[j].IsOnBoard())
					{
						return false;
					}
				}
			}

			return true;
		}
	}
}

// Check whose turn it is

bool Board::IsWhiteTurn() const
{
	return isWhiteTurn;
}

// Check the "value" for a given move (used to find out which move is best in a given situation)

double Board::ValuateMove(const Move& move) const
{
	double foo = 0;

	if (move.IsWhite())
	{
		for (int i = 0; i < 8; i++)
		{
			if (whitePieces[i].IsOnBoard())
			{
				foo += move.GetCoefficient(whitePieces[i].GetSquare().GetFile(), whitePieces[i].GetSquare().GetRank());
			}

			if (blackPieces[i].IsOnBoard())
			{
				foo -= move.GetCoefficient(blackPieces[i].GetSquare().GetFile(), blackPieces[i].GetSquare().GetRank());
			}
		}
	}

	else
	{
		for (int i = 0; i < 8; i++)
		{
			if (whitePieces[i].IsOnBoard())
			{
				foo -= move.GetCoefficient(whitePieces[i].GetSquare().GetFile(), whitePieces[i].GetSquare().GetRank());
			}

			if (blackPieces[i].IsOnBoard())
			{
				foo += move.GetCoefficient(blackPieces[i].GetSquare().GetFile(), blackPieces[i].GetSquare().GetRank());
			}
		}
	}

	return foo;
}

// Executes a given move on the board. Returns 1 if white wins after this move, -1 if black wins and 0 if game is ongoing.

int Board::ExecuteMove(const Move& move)
{
	if (move.IsWhite())
	{
		for (int i = 0; i < 8; i++)
		{
			if (whitePieces[i].GetSquare() == move.GetFrom() && whitePieces[i].IsOnBoard())
			{
				for (int j = 0; j < 8; j++)
				{
					if (blackPieces[j].GetSquare() == move.GetTo() && blackPieces[j].IsOnBoard())
					{
						blackPieces[j].SetOnBoard(false);
					}
				}

				whitePieces[i].SetSquare(move.GetTo());

				if (move.GetTo().GetRank() == 7)
				{
					return 1;
				}

				break;
			}
		}
	}

	else
	{
		for (int i = 0; i < 8; i++)
		{
			if (blackPieces[i].GetSquare() == move.GetFrom() && blackPieces[i].IsOnBoard())
			{
				for (int j = 0; j < 8; j++)
				{
					if (whitePieces[j].GetSquare() == move.GetTo() && whitePieces[j].IsOnBoard())
					{
						whitePieces[j].SetOnBoard(false);
					}
				}

				blackPieces[i].SetSquare(move.GetTo());

				if (move.GetTo().GetRank() == 0)
				{
					return -1;
				}

				break;
			}
		}
	}

	// Swap colour whose turn it is!

	if (isWhiteTurn)
	{
		isWhiteTurn = false;
	}

	else
	{
		isWhiteTurn = true;
	}

	return 0;
}

// Reset the board

void Board::ResetBoard()
{
	for (int i = 0; i < 8; i++)
	{
		whitePieces[i].SetOnBoard(true);
		whitePieces[i].SetSquare(Square(i, 1));

		blackPieces[i].SetOnBoard(true);
		blackPieces[i].SetSquare(Square(i, 6));
	}

	isWhiteTurn = true;
}

// Add a value to materialFactor

void Board::AddToMaterialFactor(double x)
{
	materialFactor += x;
}