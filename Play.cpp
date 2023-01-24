
/*********** Declaration*******
I hereby certify that no part of this assignment has been copied from
any other student’s work or from any other source. No part of the code
has been written/produced for me by another person or copied from any
other source.
I hold a copy of this assignment that I can produce if the original is
lost or damaged.
**************************/

/* Assignment 1
 * Play.cpp
 * Author: Lily Straker
*/

#include <iostream>
#include "Board.h"
using namespace std;

int main() {

//	Variables to be passed through to the class
	int boardSize;
	int pType;
	int eType;

//		Get the size of the board
		cout << "Enter the size of the board: " << endl;
		cin >> boardSize;

//		Only allow board size to be >= 3 or <= 15
		while (boardSize > 15 || boardSize < 3) {
			cout << "Enter a number between 3 and 15 (inclusive)" << endl;
			cout << "Enter the size of the board: " << endl;
			cin >> boardSize;
		}

//		Get Passer player type
		cout << "Choose your Passer player: " << endl;
		cout << "1. Human" << endl;
		cout << "2. Random AI" << endl;
		cout << "3. Straight line AI" << endl;
		cin >> pType;
		cout << endl;

//		Get Eater player type
//		If Passer player is a straight line player, then the Eater cannot be the straight line player at the same time
		if (pType == 3) {
			cout << "Choose your Eater player: " << endl;
			cout << "1. Human" << endl;
			cout << "2. Random AI" << endl;
			cin >> eType;
			cout << endl;
		}
		else {
		cout << "Choose your Eater player: " << endl;
		cout << "1. Human" << endl;
		cout << "2. Random AI" << endl;
		cout << "3. Straight line AI" << endl;
		cin >> eType;
		cout << endl;
		}

//	Create an instance of the board class and pass through variable values
	Board board(boardSize, pType, eType);
//	Begin the game!
	board.play();
}


