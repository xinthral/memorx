#ifndef __PLAYER_H__
#define __PLAYER_H__
#include <string>
using namespace std;

class Player {
private:
	string playerName = "Player";
	int playerNumber = 0;
	int playerScore = 0;
	int totalGuesses = 0;
	string playerSymbol = "*";


public:
	// Constructors
	// void inputPlayers();

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
	void setSymbol(std::istream& in) { in >> playerSymbol; }
	void setName(std::istream& in) { in >> playerName; }
	void setNumber(int number) { playerNumber = number; }
};

#endif
