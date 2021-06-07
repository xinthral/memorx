#include <ctime>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <limits>

#include "game/board.h"
#include "game/player.h"
#include "game/memorx.h"

using namespace std;

/*
 * @Author: Xinthral
 * @Date: 5/29/2021
 * Purpose: Updating this file with new features is meant to track my
 * progress as a developer, this isn't my best or fanciest work; just
 * a snapshot of where my skills are at.
*/

int main(int argc, char const *argv[]) {
    /* Normal Game */
    Memorx game;
    system("PAUSE");

    /* Overriding Extraction operator and writing to file */
    string fileName = "memorx_logfile.txt";
    ofstream oFile;
    oFile.open(fileName);
    if (oFile.fail()) {
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
