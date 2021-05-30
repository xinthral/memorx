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
