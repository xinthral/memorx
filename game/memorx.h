#ifndef __MEMORX_H__
#define __MEMORX_H__
#include <ctime>
#include <iostream>
#include <string>
#include <vector>
#include "Board.h"
#include "Player.h"

using namespace std;

class Board;
class Player;

class Memorx {
private:
	Board board;
	Player player;
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
	Memorx() {
		srand((unsigned)time(0));
		std::cout << "The game is afoot!" << std::endl;
		board.inputBoard();
		player.inputPlayers();
		play();
	}

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

	friend std::ostream& operator <<(std::ostream& out, Memorx& game) {
		vector <Player>::iterator it;
		for (it = game.playersList.begin(); it != game.playersList.end(); ++it) {
			out << "[ " << it->symbol() << " ] Name: " << it->name() << " Score: " << it->score() << std::endl;
			out << "[ " << it->symbol() << " ] Guesses: " << it->guesses() << " - Accuracy: " << (it->accuracy() == 1 ? 100 : it->accuracy()) << "%" << std::endl;
		}
		return out;
	}
	// Let the good times roll
	void play();
};

#endif
