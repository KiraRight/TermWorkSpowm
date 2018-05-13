#ifndef BOARD_H
#define BOARD_H


#include "Cell.h"
#include <ctime>
#include<stdlib.h>
#include<iostream>

using namespace std;


class Board
{
public:
	Board();
	~Board();

	void generateBoard();
	void generateShip(int nShip);
	bool checkBoard();
	Cell*** getBoard();
private:
	Cell*** board_;
	bool isGenerate_;
	const int ROWS = 10;
	const int COLUMNS = 10;
};

#endif // BOARD_H
