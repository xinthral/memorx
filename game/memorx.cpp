#include <limits>
#include <string>
#include "Memorx.h"
using namespace std;

// memorx Accessors
int Memorx::getUserGuess() {
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

// memorx Methods
void Memorx::buildPlayerList() {
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
void Memorx::displayCurrentPlayer() {
	cout << "Current Player: " << currentPlayer + 1 << endl;
	cout << "Player " << playersList[currentPlayer].number() << " [ " << playersList[currentPlayer].symbol() << " ] " << playersList[currentPlayer].name() << endl;
}
void Memorx::displayPlayerInfo() {
	vector <Player>::iterator it;
	for (it = playersList.begin(); it != playersList.end(); ++it) {
		cout << "Player " << it->number() << "  [ " << it->symbol() << " ]  " << it->name() << endl;
	}
}
void Memorx::displayScoreBoard() {
	vector <Player>::iterator it;
	for (it = playersList.begin(); it != playersList.end(); ++it) {
		cout << "[ " << it->symbol() << " ] Name: " << it->name() << " Score: " << it->score() << endl;
		cout << "[ " << it->symbol() << " ] Guesses: " << it->guesses() << " - Accuracy: " << (it->accuracy() == 1 ? 100 : it->accuracy()) << "%" << endl;
	}
}
void Memorx::getCoordinates(int input) {
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
void Memorx::incrementCurrentPlayer() {
	if (currentPlayer + 1 < numberOfPlayers)
		currentPlayer++;
	else
		currentPlayer = 0;
}
void Memorx::inputPlayers() {
	do {
		std::cout << "How many players? [1]: ";
		std::cin >> numberOfPlayers;
	} while (numberOfPlayers < 1);
}
void Memorx::takeTurn() {
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
void Memorx::play() {
	int tempCount = 0;
	Memorx::buildPlayerList();
	//cout << "Players List Build." << endl;

	board.buildBoardHidden();
	//cout << "Hidden and Shadow Boards Build." << endl;

	board.buildBoardKey();
	//cout << "Key Board Build." << endl;

	//cout << "Answer Key:" << endl;
	board.displayKey();

	do {
		//tempCount++;
		//cout << "Attempt " << tempCount << endl;
		system("PAUSE");

		board.displayBoard();
		Memorx::displayCurrentPlayer();
		Memorx::takeTurn();

	} while (keepPlaying);

	board.displayBoard();
	//displayScoreBoard();
}
