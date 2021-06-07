#include <iostream>
#include <string>
#include <vector>
#include "Board.h"
#include "Player.h"

// memorx Mutators
void Board::buildBoardKey() {
	vector <int> values;
	int sizer = (boardSize * boardSize / 2), fillCounter = 0;
	for (int i = 0; i < sizer; i++) {
		values.push_back(rand() % sizer + 1);
	}

	for (unsigned i = 0; i < values.size(); i++) {
		numberList.push_back(values[i]);
		numberList.push_back(values[i]);
	}

	for (int i = 0; i < boardSize; i++) {
		// Clear Values from values vector
		values.clear();
		for (int j = 0; j < boardSize; j++) {
			int randNum;
			randNum = rand() % (numberList.size());
			//cout << randNum << " ";
			values.push_back(numberList[randNum]);
			numberList.erase(numberList.begin() + randNum);
			fillCounter++;
		}
		//cout << endl;
		boardKey.push_back(values);
	}
}
void Board::buildBoardHidden() {
	vector <vector <int> > hboard;
	vector <vector <string> > sboard;
	int counter = 1;
	for (int i = 0; i < boardSize; i++) {
		vector <int> row;
		vector <string> srow;
		for (int j = 0; j < boardSize; j++) {
			row.push_back(counter);
			srow.push_back(to_string(counter));
			counter++;
		}
		hboard.push_back(row);
		sboard.push_back(srow);
	}
	boardHidden = hboard;
	boardShadow = sboard;
}
void Board::displayBoard() {
	string numberAdjustment = " ";
	system("CLS");

	cout << "Board Size: " << boardSize << endl;

	// Header
	//cout << string(colDivider.length() * 2 + 1, ' ');
	//for (int i = 0; i < size; i++) {
	//	cout << colDivider << i+1 << colDivider;
	//}
	cout << endl << string((colDivider.length() * 2 + 1) * boardSize, rowDivider) << endl;

	// Board
	for (int i = 0; i < boardSize; i++) {
		//cout << colDivider << i+1 << colDivider;
		for (int j = 0; j < boardSize; j++) {
			string shadowValue = boardShadow[i][j];
			if (shadowValue.length() == 1)
			cout << colDivider << " " << shadowValue << " " << colDivider;
			else if (shadowValue.length() == 2)
			cout << colDivider << " " << shadowValue << colDivider;
			else
			cout << colDivider << shadowValue << colDivider;
		}
		cout << endl;
	}
}
void Board::displayKey() {
	int counter = 0;
	for (int col = 0; col < boardSize; col++) {
		for (int row = 0; row < boardSize; row++) {
			counter++;
			cout << boardKey[col][row] << "\t";
		}
		cout << endl;
	}
}
void Board::displayScoreBoard() {

	string numberAdjustment = " ";
	system("CLS");

	cout << "Board Size: " << boardSize << endl;

	// Header
	//cout << string(colDivider.length() * 2 + 1, ' ');
	//for (int i = 0; i < size; i++) {
	//	cout << colDivider << i+1 << colDivider;
	//}
	cout << endl << string((colDivider.length() * 2 + 1) * boardSize, rowDivider) << endl;

	// Board
	for (int i = 0; i < boardSize; i++) {
		//cout << colDivider << i+1 << colDivider;
		for (int j = 0; j < boardSize; j++) {
			string shadowValue = boardShadow[i][j];
			if (shadowValue.length() == 1)
				cout << colDivider << " " << shadowValue << " " << colDivider;
			else if (shadowValue.length() == 2)
				cout << colDivider << " " << shadowValue << colDivider;
			else
				cout << colDivider << shadowValue << colDivider;
		}
		cout << endl;
	}
}
int Board::getBoardSize() {
	return boardSize;
}
void Board::inputBoard() {
	do {
		cout << "What size board would you like? \nMust be an even number [2]: ";
		cin >> boardSize;
	} while (boardSize % 2 != 0);
}
