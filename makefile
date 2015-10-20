main: Board.h LinkedList.h Move.h Piece.h Square.h
	g++ Pawns2.0.cpp -o PawnsAI -O2 -std=c++0x Board.cpp Move.cpp Piece.cpp Square.cpp