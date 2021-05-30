#include <board/board.h>
#include <player/player.h>

/*
@Author: Xinthral
@Date: 5/29/2021
Purpose: Updating this file with new features is meant to track my
progress as a developer, this isn't my best or fanciest work; just
a snapshot of where my skills are at.
*/

// memorx Constructors
memorx::memorx() {
	srand((unsigned)time(0));
	cout << "The game is afoot!" << endl;
	inputBoard();
	inputPlayers();
	play();
}

// memorx Accessors
int memorx::getBoardSize() {
	return boardSize;
}
void memorx::getCoordinates(int input) {
	for (int i = 0; i < boardSize; i++) {
		for (int j = 0; j < boardSize; j++) {
			if (boardHidden[i][j] == input) {
				coords[0] = i;
				coords[1] = j;
				break;
			}
		}
	}
}
int memorx::getUserGuess() {
	int input = -1;
	bool valid = false;
	do {
		cout << promptIcon << " ";
		cin >> input;
		if (cin.good()) {
			valid = true;
		} else {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << " Invalid input, please re-enter a valid number." << endl;
		}
	} while (!valid);

	return input;
}

// memorx Mutators
void memorx::buildBoardKey() {

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
void memorx::buildBoardHidden() {
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
void memorx::buildPlayerList() {
	Player p;
	for (int i = 0; i < numberOfPlayers; i++) {
		cout << "[ " << i + 1 << " ] Enter Player Name: ";
		p.setName(cin);
		p.setNumber(i + 1);
		cout << "[ " << i+1 << " ] Pick a symbol [*]: ";
		p.setSymbol(cin);
		playersList.push_back(p);
	}
}

void memorx::incrementCurrentPlayer() {
	if (currentPlayer + 1 < numberOfPlayers)
		currentPlayer++;
	else
		currentPlayer = 0;
}
void memorx::inputBoard() {
	do {
		cout << "What size board would you like? \nMust be an even number [2]: ";
		cin >> boardSize;
	} while (boardSize % 2 != 0);
}
void memorx::inputPlayers() {
	do {
		cout << "How many players? [1]: ";
		cin >> numberOfPlayers;
	} while (numberOfPlayers < 1);
}

// memorx Methods
void memorx::displayBoard() {
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
void memorx::displayCurrentPlayer() {
	cout << "Current Player: " << currentPlayer + 1 << endl;
	cout << "Player " << playersList[currentPlayer].number() << " [ " << playersList[currentPlayer].symbol() << " ] " << playersList[currentPlayer].name() << endl;
}
void memorx::displayKey() {
	int counter = 0;
	for (int col = 0; col < boardSize; col++) {
		for (int row = 0; row < boardSize; row++) {
			counter++;
			cout << boardKey[col][row] << "\t";
		}
		cout << endl;
	}
}
void memorx::displayPlayerInfo() {
	vector <Player>::iterator it;
	for (it = playersList.begin(); it != playersList.end(); ++it) {
		cout << "Player " << it->number() << "  [ " << it->symbol() << " ]  " << it->name() << endl;
	}
}
void memorx::displayScoreBoard() {
	vector <Player>::iterator it;
	for (it = playersList.begin(); it != playersList.end(); ++it) {
		cout << "[ " << it->symbol() << " ] Name: " << it->name() << " Score: " << it->score() << endl;
		cout << "[ " << it->symbol() << " ] Guesses: " << it->guesses() << " - Accuracy: " << (it->accuracy() == 1 ? 100 : it->accuracy()) << "%" << endl;
	}
}
ostream& operator << (ostream& out, memorx& game) {
	vector <Player>::iterator it;
	for (it = game.playersList.begin(); it != game.playersList.end(); ++it) {
		out << "[ " << it->symbol() << " ] Name: " << it->name() << " Score: " << it->score() << endl;
		out << "[ " << it->symbol() << " ] Guesses: " << it->guesses() << " - Accuracy: " << (it->accuracy() == 1 ? 100 : it->accuracy()) << "%" << endl;
	}
	return out;
}
void memorx::takeTurn() {
	int inputOne = -1, inputTwo = -1, guess = -1, coordOne[2], coordTwo[2];
	bool repeat1 = true, repeat2 = true;

	// Loop awaiting proper input for first guess
	while (inputOne < 0 || inputOne > boardSize*boardSize || repeat1 == true) {
		guess = 0;
		fill(begin(coords), end(coords), 0);
		cout << "First Choice [1-" << boardSize * boardSize << "]" << endl;

		//cin >> inputOne;  // Instructional
		inputOne = getUserGuess();

		getCoordinates(inputOne);
		coordOne[0] = coords[0];
		coordOne[1] = coords[1];
		string iOne = to_string(inputOne);
		if (iOne != boardShadow[coordOne[0]][coordOne[1]]) {
			cout << "Tile already chosen, try another..." << endl;
			repeat1 = true;
		}
		else
			repeat1 = false;
	}

	// Loop awaiting proper input for second guess
	while (inputTwo < 0 || inputTwo > boardSize*boardSize || inputTwo == inputOne || repeat2 == true) {
		fill(begin(coords), end(coords), 0);
		cout << "Second Choice [1-" << boardSize * boardSize << "]: ";
		inputTwo = getUserGuess();
		getCoordinates(inputTwo);
		coordTwo[0] = coords[0];
		coordTwo[1] = coords[1];
		string iTwo = to_string(inputTwo);
		if (iTwo != boardShadow[coordTwo[0]][coordTwo[1]]) {
			cout << "Number has already been choice, try another..." << endl;
			repeat2 = true;
		}
		else
			repeat2 = false;
	}

	// Validate if the coordinates of user guesses match on boardkey
	if (keepPlaying) {
		if (boardKey[coordOne[0]][coordOne[1]] != boardKey[coordTwo[0]][coordTwo[1]]) {
			cout << "Incorrect Answer!" << endl;
			//playersList[currentPlayer].decrementScore();
			cout << "[ " << inputOne << " ]: " << boardKey[coordOne[0]][coordOne[1]] << endl;
			cout << "[ " << inputTwo << " ]: " << boardKey[coordTwo[0]][coordTwo[1]] << endl;
		}
		else {
			cout << "Correct Answer!" << endl;
			playersList[currentPlayer].incrementScore();
			cout << "[ " << boardKey[coordOne[0]][coordOne[1]] << " ] was the hidden value." << endl;
			boardShadow[coordOne[0]][coordOne[1]] = playersList[currentPlayer].symbol();
			boardShadow[coordTwo[0]][coordTwo[1]] = playersList[currentPlayer].symbol();
			correct++;
		}

		playersList[currentPlayer].incrementGuess();
		incrementCurrentPlayer();

		// If number of correct answers reaches the number of elements, round ends.
		if (correct >= (boardSize * boardSize / 2)) {
			cout << endl << "==================================\nThis round has been concluded!\n==================================" << endl;
			keepPlaying = false;
		}
	}
}

// memorx Game On
void memorx::play() {
	int tempCount = 0;
	buildPlayerList();
	//cout << "Players List Build." << endl;

	buildBoardHidden();
	//cout << "Hidden and Shadow Boards Build." << endl;

	buildBoardKey();
	//cout << "Key Board Build." << endl;

	//cout << "Answer Key:" << endl;
	displayKey();

	do {
		//tempCount++;
		//cout << "Attempt " << tempCount << endl;
		system("PAUSE");

		displayBoard();
		displayCurrentPlayer();
		takeTurn();

	} while (keepPlaying);

	displayBoard();
	//displayScoreBoard();
}
