// Pawns2.0.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "Board.h"
#include "LinkedList.h"
#include <vector>
#include <ctime>
#include <fstream>

using std::vector;

// Test change for Git

// GLOBAL CONSTANTS

const double GLOBAL_MAXVALUE = -1000000;
const double GLOBAL_ADJUST = 0.1;

// PROTOTYPES

vector<Move> PopulateMoves();
bool HumanVsAI(Board& board, vector<Move>& moves, vector<Move>& game, bool output);
bool GameLoop(Board&, vector<Move>&, vector<Move>&, bool);
int HumanTurnLoop(Board&, vector<Move>&, vector<Move>&, bool);
int AITurnLoop(Board&, vector<Move>&, vector<Move>&, bool);
void AdjustCoefficients(Board&, vector<Move>&, vector<Move>&, bool);

// MAIN

int _tmain(int argc, _TCHAR* argv[])
{
	int NUMBER_OF_GAMES;

	bool choice;
	char charchoice;

	cout << "Would you like to watch a game after the program has run? Y for yes, not Y for no.";
	cin >> charchoice;

	if (charchoice == 'Y' || charchoice == 'y')
	{
		choice = true;
	}

	else
	{
		choice = false;
	}

	cout << "Enter a number of games to loop: ";
	cin >> NUMBER_OF_GAMES;

	srand(time(NULL));

	Board board = Board();
	vector<Move> allMoves = PopulateMoves();
	vector<Move> currentGame;

	for (int i = 1; i <= NUMBER_OF_GAMES; i++)
	{
		bool result = GameLoop(board, allMoves, currentGame, false);

		AdjustCoefficients(board, currentGame, allMoves, result);

		board.ResetBoard();
		currentGame.clear();

		if (i % 1000 == 0)
		{
			cout << "Game " << i << " complete.\n";
		}
	}

	cout << "Learning complete. Beginning final game." << endl;
	cin.get();

	ofstream os;

	os.open("coefficients.txt", std::ofstream::out | std::ofstream::trunc);

	if (os.is_open())
	{
		for (int i = 0; i < allMoves.size(); i++)
		{
			for (int j = 0; j < 8; j++)
			{
				for (int k = 0; k < 8; k++)
				{
					os << allMoves[i].GetCoefficient(j, k) << "\n";
				}
			}
		}
	}

	os.close();

	cout << "Would you like to play a game? Y for yes, not Y for no.\n";
	cin >> charchoice;

	if (charchoice == 'Y' || charchoice == 'y')
	{
		HumanVsAI(board, allMoves, currentGame, true);
	}

	else
	{
		GameLoop(board, allMoves, currentGame, choice);
	}
}

// PopulateMoves should be called once to generate a candidate move list. Each move is then checked each turn for validity.

vector<Move> PopulateMoves()
{
	vector<Move> end;

	// Populate all white moves:
	// 1. All moves one square straight forward
	// 2. All moves one square forward and one square right/left
	// 3. All moves two squares forward starting on rank 1

	for (int i = 0; i < 8; i++)
	{
		for (int j = 1; j <= 6; j++)
		{
			end.push_back(Move(Square(i, j), Square(i, j + 1), true));

			if (i != 0)
			{
				end.push_back(Move(Square(i, j), Square(i - 1, j + 1), true));
			}

			if (i != 8)
			{
				end.push_back(Move(Square(i, j), Square(i + 1, j + 1), true));
			}

			if (j == 1)
			{
				end.push_back(Move(Square(i, j), Square(i, j + 2), true));
			}
		}
	}

	// Populate all black moves: see all white moves, but in reverse

	for (int i = 0; i < 8; i++)
	{
		for (int j = 1; j <= 6; j++)
		{
			end.push_back(Move(Square(i, j), Square(i, j - 1), false));

			if (i != 0)
			{
				end.push_back(Move(Square(i, j), Square(i - 1, j - 1), false));
			}

			if (i != 8)
			{
				end.push_back(Move(Square(i, j), Square(i + 1, j - 1), false));
			}

			if (j == 6)
			{
				end.push_back(Move(Square(i, j), Square(i, j - 2), false));
			}
		}
	}

	ifstream ifs;

	ifs.open("coefficients.txt");

	if (ifs.is_open())
	{
		double value;

		for (int i = 0; i < end.size(); i++)
		{
			for (int j = 0; j < 8; j++)
			{
				for (int k = 0; k < 8; k++)
				{
					ifs >> value;

					end[i].AddToCoefficient(j, k, value);
				}
			}
		}
	}

	return end;
}

// HumanVsAI runs a game where the human has white and the computer has black. The computer does not learn from these games.

bool HumanVsAI(Board& board, vector<Move>& moves, vector<Move>& game, bool output)
{
	do
	{
		int temp = HumanTurnLoop(board, moves, game, output);

		if (temp == 1)
		{
			return true;
		}

		else if (temp == -1)
		{
			return false;
		}

		temp = AITurnLoop(board, moves, game, output);

		if (temp == 1)
		{
			return true;
		}

		else if (temp == -1)
		{
			return false;
		}

	} while (true);
}

// GameLoop runs the game itself. It returns true for a white win, false for a black win.

bool GameLoop(Board& board, vector<Move>& moves, vector<Move>& game, bool output)
{
	do
	{
		int temp = AITurnLoop(board, moves, game, output);

		if (temp == 1)
		{
			return true;
		}

		else if (temp == -1)
		{
			return false;
		}

	} while (true);
}

// HumanTurnLoop runs each individual human turn. It returns 1 for a white win, -1 for a black win and 0 if the game is still in progress

int HumanTurnLoop(Board& board, vector<Move>& moves, vector<Move>& game, bool output)
{
	vector<Move> validMoves;

	if (output)
	{
		cout << board;
		cin.get();
	}

	// Figure out all valid moves

	for (int i = 0; i < moves.size(); i++)
	{
		if (board.IsMoveValid(moves[i]))
		{
			validMoves.push_back(moves[i]);
		}
	}

	// If there are none, game is over!

	if (validMoves.size() == 0)
	{
		if (board.IsWhiteTurn())
		{
			if (output)
			{
				cout << "No more moves for white. Game over!\n";
			}

			return -1;
		}

		else
		{
			if (output)
			{
				cout << "No more moves for black. Game over!\n";
			}

			return 1;
		}
	}

	// Prompt human for input until they type in a valid move, then execute that move

	do
	{
		int fileFrom, rankFrom, fileTo, rankTo;

		cout << "Enter the file of the square you are moving from: ";
		cin >> fileFrom;

		cout << "Enter the rank of the square you are moving from: ";
		cin >> rankFrom;

		cout << "Enter the file of the square you are moving to: ";
		cin >> fileTo;

		cout << "Enter the rank of the square you are moving to: ";
		cin >> rankTo;

		fileFrom -= 1;
		rankFrom -= 1;
		fileTo -= 1;
		rankTo -= 1;

		Square newFrom = Square(fileFrom, rankFrom);
		Square newTo = Square(fileTo, rankTo);
		Move candidateMove = Move(newFrom, newTo, true);

		for (int i = 0; i < validMoves.size(); i++)
		{
			if (validMoves[i].GetFrom() == newFrom && validMoves[i].GetTo() == newTo)
			{
				game.push_back(candidateMove);

				return board.ExecuteMove(candidateMove);
			}
		}

		cout << "That move is not allowed. Try again!\n";

	} while (true);
}

// AITurnLoop runs each individual AI turn. It returns 1 for a white win, -1 for a black win and 0 if the game is still in progress

int AITurnLoop(Board& board, vector<Move>& moves, vector<Move>& game, bool output)
{
	vector<Move> validMoves;
	vector<Move> candidateMoves;

	if (output)
	{
		cout << board;
		cin.get();
	}

	// Figure out all valid moves

	for (int i = 0; i < moves.size(); i++)
	{
		if (board.IsMoveValid(moves[i]))
		{
			validMoves.push_back(moves[i]);
		}
	}

	// If there are none, game is over!

	if (validMoves.size() == 0)
	{
		if (board.IsWhiteTurn())
		{
			if (output)
			{
				cout << "No more moves for white. Game over!\n";
			}

			return -1;
		}

		else
		{
			if (output)
			{
				cout << "No more moves for black. Game over!\n";
			}

			return 1;
		}
	}

	// Figure out which of the valid moves are best

	double maxValue = GLOBAL_MAXVALUE;

	for (int i = 0; i < validMoves.size(); i++)
	{
		double result = board.ValuateMove(validMoves[i]);

		if (result > maxValue)
		{
			maxValue = result;

			candidateMoves.clear();
			candidateMoves.push_back(validMoves[i]);
		}

		else if (result == maxValue)
		{
			candidateMoves.push_back(validMoves[i]);
		}

		else if (result < GLOBAL_MAXVALUE)
		{
			cout << "ValuateMove returned a value below maxValue default." << endl;

			cout << "result is: " << result << endl;

			cin.get();
		}
	}

	int foo = rand() % candidateMoves.size();

	/*
	cout << "Move chosen: " << endl;
	cout << candidateMoves[foo];
	cin.get();
	*/

	int bar = board.ExecuteMove(candidateMoves[foo]);

	/*
	cout << "bar is: " << bar << endl;
	cin.get();
	*/

	game.push_back(candidateMoves[foo]);

	/*
	cout << "link appended" << endl;
	cin.get();
	*/

	if (output)
	{
		cout << "Move made:\n";
		cout << candidateMoves[foo];
		cin.get();
	}

	return bar;
}

/*
	AdjustCoefficients() takes a completed game and:
	1. For each move the winning player made, adjusts the entries in the move's coefficient matrix upwards if a piece appeared on that
	   square.
	2. For each move the losing player made, adjusts the entries in the move's coefficient matrix downwards if a piece appeared on that
	   square.
*/

void AdjustCoefficients(Board& board, vector<Move>& game, vector<Move>& allMoves, bool whiteWon)
{
	board.ResetBoard();

	for (int i = 0; i < game.size(); i++)
	{
		if (whiteWon)
		{
			if (game[i].IsWhite())
			{
				for (int j = 0; j < allMoves.size(); j++)
				{
					if (allMoves[j].GetFrom() == game[i].GetFrom() && allMoves[j].GetTo() == game[i].GetTo() && allMoves[j].IsWhite() == game[i].IsWhite())
					{
						for (int k = 0; k < 8; k++)
						{
							allMoves[j].AddToCoefficient(board.GetWhitePiece(k).GetSquare().GetFile(), board.GetWhitePiece(k).GetSquare().GetRank(), GLOBAL_ADJUST);
							allMoves[j].AddToCoefficient(board.GetBlackPiece(k).GetSquare().GetFile(), board.GetBlackPiece(k).GetSquare().GetRank(), -1 * GLOBAL_ADJUST);
						}

						break;
					}
				}
			}

			else
			{
				for (int j = 0; j < allMoves.size(); j++)
				{
					if (allMoves[j].GetFrom() == game[i].GetFrom() && allMoves[j].GetTo() == game[i].GetTo() && allMoves[j].IsWhite() == game[i].IsWhite())
					{
						for (int k = 0; k < 8; k++)
						{
							allMoves[j].AddToCoefficient(board.GetWhitePiece(k).GetSquare().GetFile(), board.GetWhitePiece(k).GetSquare().GetRank(), GLOBAL_ADJUST);
							allMoves[j].AddToCoefficient(board.GetBlackPiece(k).GetSquare().GetFile(), board.GetBlackPiece(k).GetSquare().GetRank(), -1 * GLOBAL_ADJUST);
						}

						break;
					}
				}
			}
		}

		else
		{
			if (game[i].IsWhite())
			{
				for (int j = 0; j < allMoves.size(); j++)
				{
					if (allMoves[j].GetFrom() == game[i].GetFrom() && allMoves[j].GetTo() == game[i].GetTo() && allMoves[j].IsWhite() == game[i].IsWhite())
					{
						for (int k = 0; k < 8; k++)
						{
							allMoves[j].AddToCoefficient(board.GetWhitePiece(k).GetSquare().GetFile(), board.GetWhitePiece(k).GetSquare().GetRank(), -1 * GLOBAL_ADJUST);
							allMoves[j].AddToCoefficient(board.GetBlackPiece(k).GetSquare().GetFile(), board.GetBlackPiece(k).GetSquare().GetRank(), GLOBAL_ADJUST);
						}

						break;
					}
				}
			}

			else
			{
				for (int j = 0; j < allMoves.size(); j++)
				{
					if (allMoves[j].GetFrom() == game[i].GetFrom() && allMoves[j].GetTo() == game[i].GetTo() && allMoves[j].IsWhite() == game[i].IsWhite())
					{
						for (int k = 0; k < 8; k++)
						{
							allMoves[j].AddToCoefficient(board.GetWhitePiece(k).GetSquare().GetFile(), board.GetWhitePiece(k).GetSquare().GetRank(), -1 * GLOBAL_ADJUST);
							allMoves[j].AddToCoefficient(board.GetBlackPiece(k).GetSquare().GetFile(), board.GetBlackPiece(k).GetSquare().GetRank(), GLOBAL_ADJUST);
						}

						break;
					}
				}
			}
		}

		board.ExecuteMove(game[i]);
	}
}