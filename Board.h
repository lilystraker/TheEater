/* Assignment 1
 * Board.h
 * Author: Lily Straker
*/

#include <string>
using namespace std;
#ifndef BOARD_H_
#define BOARD_H_

// Create Board class
class Board {
//	Set private variables
	private:
	int boardSize;
	int** gameBoard;
	int passerType;
	int eaterType;
	int maxMoves;

//	Set public methods
	public:
//	Constructor method
	Board(int, int, int);

	bool isValidMove(int x, int y, int player);

	bool getPMoveHuman(int &x, int &y);
	bool getPMoveRandom(int &x, int &y);
	bool getPMoveLine(int &x, int &y);

	bool getEMoveHuman(int &x, int &y);
	bool getEMoveRandom(int &x, int &y);
	bool getEMoveLine(int &x, int &y);

	bool foundPasserPath(int x, int y, string ListMove="no");

	void addMove(int x, int y, int player, int &noOfMoves);

	int gameStatus(int noOfMoves, int maxMoves, int &x, int &y);

	int play();
	void display();

//	Destructor method
	~Board();
};




#endif /* BOARD_H_ */
