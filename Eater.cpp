
/*********** Declaration*******
I hereby certify that no part of this assignment has been copied from
any other student’s work or from any other source. No part of the code
has been written/produced for me by another person or copied from any
other source.
I hold a copy of this assignment that I can produce if the original is
lost or damaged.
**************************/

/* Assignment 1
 * Eater.cpp
 * Author: Lily Straker
*/

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include "Board.h"
using namespace std;

string lastMoveList[5] = {"Left", "LeftUp", "Up", "RightUp", "Right"};
bool pathFound = false;

// Constructor method
// This runs when an instance of the Board class is called
Board::Board (int size, int pType, int eType) {
	boardSize = size;
//	Allocate memory
//	Set an array of pointers
	gameBoard = new int*[boardSize];
//	Determine the passer and eater type
	passerType = pType;
	eaterType = eType;
	maxMoves = boardSize * boardSize;

//	Each pointer within the array points to an array of integers
	for (int i = 0; i < boardSize; i++) {
		gameBoard[i] = new int[boardSize];
	}

// Set these integers to 0
    for (int i = 0; i < boardSize; i++) {
      for (int j = 0; j < boardSize; j++) {
    	  gameBoard[i][j] = 0;
      }
    }

}

// Check whether the player enters a valid move
bool Board::isValidMove(int x, int y, int player) {

//	Passer player
	if (player == 1) {
		// Invalid move if position out of boundary
		if ((0 > x) || (x > boardSize - 1) || (0 > y) || (y > boardSize - 1) ) {
//			If the passer player isn't human, do not print this text
			if (passerType == 1) {
				cout << "Your coordinates must be between 1 and " <<  boardSize << " inclusive." << endl << "Try again: " << endl;
			}
			return false;
		}
		// Invalid move if position already occupied
		else if (gameBoard[x][y] != 0)
		{
			if (passerType == 1) {
				cout << "Your coordinate position has already been occupied." <<  endl << "Try again: " << endl;
			}
			return false;

		}

	}
//	Eater player
	if (player == -1) {

		// Invalid move if position out of boundary
		if ((0 > x) || (x > boardSize - 1) || (0 > y) || (y > boardSize - 1) ) {
			// If the eater player isn't human, do not print this text
			if (eaterType == 1) {
				cout << "Your coordinates must be between 1 and " <<  boardSize << " inclusive." << endl << "Try again: " << endl;
			}
			return false;
		}
//		Invalid move if Eater already occupies the position
		else if (gameBoard[x][y] == -1) {
			if (eaterType == 1) {
				cout << "You already occupy that position." << endl;
			}
			return false;
		}
//		Valid move if Passer already occupies position
		else if (gameBoard[x][y] == 1)
		{
			return true;

		}
	}

	return true;

}
// If the Passer player is human, prompt the user for their position
bool Board::getPMoveHuman(int &x, int &y) {

	int row, col;
//	Check whether the move is valid
//	Prompt user again if move is not valid
	do {
		cin >> row >> col;
		cout << endl;

	} while (!isValidMove(row - 1, col - 1, 1));

//	Update x and y values;
	x = row - 1;
	y = col - 1;
	return true;
}

// If the Passer player is the random AI
bool Board::getPMoveRandom(int &x, int &y) {
//	Set seed number
	srand(time(0));

	do {
//		Ensure x and y values are within range of the board
		x = rand() % boardSize;
		y = rand() % boardSize;
	} while (!isValidMove(x, y, 1));

	return true;
}

// If the Passer player is the straight line AI
bool Board::getPMoveLine(int &x, int &y) {
	x = -1;
	y = 0;
	do {
//		If the position is taken, increment x value so that the player moves to the position directly below
		x++;
//		If the player reaches the last row, move to the first row of the next column
		if (x >= boardSize) {
			x = 0;
			y++;
		}

	} while (!isValidMove(x, y, 1));
	return true;
}

// Human eater player
bool Board::getEMoveHuman(int &x, int &y) {
	int row, col;
	do {
		cin >> row >> col;
		cout << endl;

	} while (!isValidMove(row - 1, col - 1, -1));
	x = row - 1;
	y = col - 1;
	return true;
}

// Random AI Eater player
bool Board::getEMoveRandom(int &x, int &y) {

	do {
		x = rand() % boardSize;
		y = rand() % boardSize;
	} while (!isValidMove(x, y, -1));
	return true;
}

// Straight line AI Eater player
bool Board::getEMoveLine(int &x, int &y) {
	x = -1;
	y = 0;
	do {
		x++;
		if (x >= boardSize) {
			x = 0;
			y++;
		}

	} while (!isValidMove(x, y, 1));
	return true;
}

// Check whether the passer has formed a continuous, valid path from the bottom row to the top row
bool Board::foundPasserPath(int x, int y, string lastMove) {

/*	When there is a Passer token in the last row of the board, this function is called with the passer's x and y values that were just
  	inputted. This function then checks the left, upleft, up, upright, and right values (assuming they aren't out of range)
	surrounding the passer's position. If there is a Passer token in any of these positions, a 1 is inserted into the array in the
	appropriate spot.
	Then, we loop over this array. When a 1 is found, the foundPasserPath function is recursively called, using the corresponding x and
	y value. This function repeats until either:
	- the path reaches the topmost row (when x = 0), at which point a path has been found
	- the path has no surrounding Passer tokens, so a path has not been found. The function will continue to check the rest of the
	  positions until it either finds a path or can definitively say there is no path yet.
*/

	//	Each position in this array represents the following order:
	// 		Left, Upleft, Up, Upright, Right
	//	Initialise the array with 0s
	  int pathVariations[5] = {0,0,0,0,0};
	    if (x == 0) {
	      pathFound = true;
	      return true;
	    }

//	    		Check the left value
//	    		If this value has been checked before, skip over it.
//	    		This is to prevent any loops whether the function goes
//	    		left -> right -> left -> right... and so on.
//	    		If the token is in the first column, there will be no value to the left
	    		if (gameBoard[x][y-1] == 1 && lastMove != "Right" && y >= 1) {
	    			pathVariations[0] = 1;

	    		}
//	    		Check the top left value
//	    		If the token is in the first column, there will be no top left value
	            if (gameBoard[x - 1][y - 1] == 1 && x >= 1 && y >= 1) {
	                pathVariations[1] = 1;
	            }
//	            Check the above value
	            if (gameBoard[x - 1][y] == 1 && x >= 1) {
	                pathVariations[2] = 1;
	            }
//	            Check the top right value
//	            If the token is in the last column, there will be no top right value
	            if (gameBoard[x - 1][y + 1] == 1 && x >= 1 && y < boardSize) {
	                pathVariations[3] = 1;
	            }
//	            Check the right value
// 				If the token is in the last column, there will be no right value
	    		if (gameBoard[x][y+1] == 1 && lastMove != "Left" && y < boardSize) {
	    			pathVariations[4] = 1;
	    		}

//

//	    		Check each value in the pathVariations array
	            for (int i = 0; i < 5; i++) {
//	            	If there is a 1, call checkPasserFunction with the x and y values that correspond with the position
//	            	e.g. if there is a 1 in the 0th index of the array, there must be a token to the left of the current position.
//	            	So, the function will be called with the x and y values of the left token
	                if (pathVariations[i] == 1) {
	                	lastMove = lastMoveList[i];
//	                	If there is a token to the right
	                	if (i == 4) {
	                		foundPasserPath(x, y + 1, lastMove);
	                	}
//	                	If there is a token to the left
	                	else if (i == 0) {
	                		foundPasserPath(x, y - 1, lastMove);

	                	}
//						If the token is either in the topleft, top, or topright
	                	else {
	                        foundPasserPath(x - 1, y + i - 2, lastMove);

	                	}
	                }
	            }

//	            If a path has been found, the function is true
	            if (pathFound) {
	              return true;
	            }
	            else {
	            	return false;
	            }
}

// Add the player's move to the board
void Board::addMove(int x, int y, int player, int &noOfMoves) {
//  Increment the number of moves taken only if either:
//		- The Passer takes a square that the Eater does not then immediately take
//		- The Eater takes a square that is not already occupied by the Passer
	if ((player == 1) || (player == -1 && gameBoard[x][y] != 1)) {
		noOfMoves++;
	}
//	Add move to the board
	gameBoard[x][y] = player;

}

// Check whether the game has finished
int Board::gameStatus(int noOfMoves, int maxMoves, int &x, int &y) {

// Check if Passer occupies any position in the last row
      for (int j = 0; j < boardSize; j++) {
    		  if (gameBoard[boardSize - 1][j] == 1) {
    			  if (foundPasserPath(boardSize - 1, j)) {
    		    	  pathFound = true;
//    		    	  If path is found, Passer wins
    		    	  return 1;
    		      }
    		      else if (noOfMoves >= maxMoves) {
//    		    	  If there are no moves left, Eater wins
    		    	  return 2;
    		      }

    	  }

    	  }
    return 0;

}

// Create the visual output of the board
void Board::display() {
// 		Print column numbers
		for (int l = 0; l < boardSize; l++) {
			cout << "   " << l + 1;
		}
		cout << endl << "  _";
//		Print a horizontal line
		for (int l = 0; l < boardSize; l++) {

			cout << "____";
		}
		cout << endl;
//		Print vertical lines
		for (int i = 0; i < boardSize; i++) {
//			Add a space after the row number if it is a single digit
			if (i < 9) {
				cout << i + 1 << ' ' << '|';
			}
//			Double digit numbers
			else {
				cout << i + 1 << '|';
			}
//			Set playersymbols
			for (int j = 0; j < boardSize; j++) {

				char playerSymbol = ' ';
				if (gameBoard[i][j] == 1)
					playerSymbol = 'P';
				else if (gameBoard[i][j] == -1)
					playerSymbol = 'E';
//				Set size of the squares
				cout << setw(3) << playerSymbol;

				if (j != boardSize) {
					cout << "|";
				}
			}
			cout << endl;
//			Print the second vertical line in each row, along with horizontal lines to separate the rows
			if (i != boardSize) {
				cout << "  ";
				for (int k = 0; k < boardSize; k++) {
					cout << "|___";
				}
//				End with a vertical line
				cout << "|" << endl;
			}
		}
		cout << endl;
}

// Destructor method for the class
Board::~Board() {
//	Deallocate memory for the pointers within the array
		for (int i = 0; i < boardSize; i++)
			delete[] gameBoard[i];
//		Deallocate memory for the array itself
		delete[] gameBoard;

}

// This method is called from the class driver
int Board::play() {
//	Initialise number of moves to 0
	int noOfMoves = 0;
//	Set first player to Passer player
	int player = 1;

//	Display the game board
	display();

//	Intialise the state of the game (0 = not finished)
	int done = 0;
//			While game is not finished
			while (done == 0) {
				player = 1;
	//			if player is the passer, then player symbol is P. If player is the eater, player symbol is E
				char playerSymbol = (player == 1) ? 'P' : 'E';
//				Passer player's x and y values
				int xp, yp;
//				Eater player's x and y values
				int xe, ye;

	//			Passer player
				if (player == 1) {

					playerSymbol = 'P';
//					If the passer player is human
					if (passerType == 1) {
						cout << "Player " << playerSymbol << " enter move: " << endl;
					}
//					Determine which move function to be called, depending on the type of passer player
						switch (passerType) {
						case 1:
							getPMoveHuman(xp, yp);
							break;
						case 2:
							getPMoveRandom(xp, yp);
							break;
						case 3:
							getPMoveLine(xp, yp);
							break;
						default:
							getPMoveHuman(xp, yp);
						}
//					Set player to Eater
					player = -1;

				}
	//			Eater
				if (player == -1) {
					playerSymbol = 'E';
//					If Eater player is human, print output
					if (eaterType == 1) {
						cout << "Player " << playerSymbol << " enter move: " << endl;
					}
//					Determine which move function to be called, depending on the type of eater player
					switch (eaterType) {
					case 1:
						getEMoveHuman(xe, ye);
						break;
					case 2:
						getEMoveRandom(xe, ye);
						break;
					case 3:
						getEMoveLine(xe, ye);
						break;
					default:
						getEMoveHuman(xe, ye);
					}

	//				If Passer and Eater place a token on the same square, only register Eater's move, otherwise add both moves
					if ((xp != xe) || (yp != ye)) {
						addMove(xp, yp, 1, noOfMoves);
						addMove(xe, ye, -1, noOfMoves);

					} else {
						addMove(xe, ye, -1, noOfMoves);

					}
//					Display the game board with new moves added
					display();

//					Set player to passer
					player = 1;

					}

//				Check the status of the game
				done = gameStatus(noOfMoves, maxMoves, xp, yp);
				switch (done) {
//				Game has not finished
				case 0:
					break;
//				Passer player wins
				case 1:
					cout << "Passer wins!";
					return 0;
//				Eater player wins
				case 2:
					cout << "Eater wins!";
					return 0;
				default:
					break;

				}
			}

	return 0;
}





