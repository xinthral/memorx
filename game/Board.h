#ifndef __BOARD_H__
#define __BOARD_H__
#include <string>
#include <vector>
using namespace std;

class Board {
private:
    int boardSize = 2;
    char rowDivider = '-', promptIcon = '>';
    string colDivider = " | ";
    vector< vector <int> > boardKey, boardHidden;
    vector< vector <string> > boardShadow;
    vector <int> numberList;

public:
    void buildBoardKey();
	void buildBoardHidden();
    void displayBoard();
    void displayKey();
    void displayScoreBoard();
    int getBoardSize();
    void inputBoard();
};

#endif
