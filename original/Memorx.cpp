#include <ctime>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <limits>
using namespace std;

/*	@Author	: Xinthral
	@Date	: April 13, 2018
	Purpose	: MemorX is a Memory game clone
*/

class Player {
private:

	string playerName = "Player";
	int playerNumber = 0;
	int playerScore = 0;
	int totalGuesses = 0;
	string playerSymbol = "*";

public:
	// Constructors
	//Player();

	// Accessors
	double accuracy() { return  ((playerScore * 1.0) / totalGuesses) * 100; }
	int guesses() { return totalGuesses; }
	string name() { return playerName; }
	int number() { return playerNumber; }
	int score() { return playerScore; }
	string symbol() { return playerSymbol; }

	// Mutators
	void incrementGuess() { totalGuesses++; }
	void incrementScore() { playerScore++; }
	// Deprecated Mutator
	//void decrementScore() { if (playerScore > 0) playerScore--; }
	void setSymbol(istream& in) { in >> playerSymbol; }

	void setName(istream& in) { in >> playerName; }
	void setNumber(int number) { playerNumber = number; }

};
class Memorx {
private:
	bool keepPlaying = true;
	char rowDivider = '-', promptIcon = '>';
	int numberOfPlayers = 1, boardSize = 2, currentPlayer = 0, correct = 0, coords[2];
	string playerName = "Player", colDivider = " | ";
	vector <Player> playersList;
	vector <int> numberList;
	vector< vector <int> > boardKey, boardHidden;
	vector< vector <string> > boardShadow;

public:
	// Constructors
	Memorx();

	// Accessors
	int getBoardSize();
	void getCoordinates(int);
	int getUserGuess();

	// Mutators
	void buildBoardKey();
	void buildBoardHidden();
	void buildPlayerList();
	void incrementCurrentPlayer();
	void inputBoard();
	void inputPlayers();

	// Methods
	void displayBoard();
	void displayCurrentPlayer();
	void displayKey();
	void displayPlayerInfo();
	void displayScoreBoard();
	void takeTurn();

	friend ostream& operator <<(ostream&, Memorx&);
	// Let the good times roll
	void play();
};

int main() {
	/* Normal Game */
	Memorx game;
	system("PAUSE");

	/* Overriding Extraction operator and writing to file */
	string fileName = "memorx_logfile.txt";
	ofstream oFile;
	oFile.open(fileName);
	if (oFile.fail())
	{
		char junk;
		cout << "Output file failed to open! ";
		cout << "Press any key to continue...";
		cin >> junk;
		exit(2);
	} else {
		cout << "Writing to: " << fileName << endl;
		oFile << game;
	}
	oFile.close();
	return 0;
}

// Method Definitions
// Memorx Constructors
Memorx::Memorx() {
	srand((unsigned)time(0));
	cout << "The game is afoot!" << endl;
	inputBoard();
	inputPlayers();
	play();
}

// Memorx Accessors
int Memorx::getBoardSize() {
	return boardSize;
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

// Memorx Mutators
void Memorx::buildBoardKey() {

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
void Memorx::buildBoardHidden() {
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
void Memorx::incrementCurrentPlayer() {
	if (currentPlayer + 1 < numberOfPlayers)
		currentPlayer++;
	else
		currentPlayer = 0;
}
void Memorx::inputBoard() {
	do {
		cout << "What size board would you like? \nMust be an even number [2]: ";
		cin >> boardSize;
	} while (boardSize % 2 != 0);
}
void Memorx::inputPlayers() {
	do {
		cout << "How many players? [1]: ";
		cin >> numberOfPlayers;
	} while (numberOfPlayers < 1);
}

// Memorx Methods
void Memorx::displayBoard() {
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
void Memorx::displayCurrentPlayer() {
	cout << "Current Player: " << currentPlayer + 1 << endl;
	cout << "Player " << playersList[currentPlayer].number() << " [ " << playersList[currentPlayer].symbol() << " ] " << playersList[currentPlayer].name() << endl;
}
void Memorx::displayKey() {
	int counter = 0;
	for (int col = 0; col < boardSize; col++) {
		for (int row = 0; row < boardSize; row++) {
			counter++;
			cout << boardKey[col][row] << "\t";
		}
		cout << endl;
	}
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
ostream& operator << (ostream& out, Memorx& game) {
	vector <Player>::iterator it;
	for (it = game.playersList.begin(); it != game.playersList.end(); ++it) {
		out << "[ " << it->symbol() << " ] Name: " << it->name() << " Score: " << it->score() << endl;
		out << "[ " << it->symbol() << " ] Guesses: " << it->guesses() << " - Accuracy: " << (it->accuracy() == 1 ? 100 : it->accuracy()) << "%" << endl;
	}
	return out;
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

// Memorx Game On
void Memorx::play() {
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
