#ifndef BOARD_H
#define BOARD_H

#include "Cell.h"

#include <ctime>
#include<stdlib.h>
#include<iostream>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>

#define BUFLEN 30

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
    void analize(int status,int x, int y);
    int returnstatus(int x,int y, int sockfd);
    bool checkHit(int x, int y);
    int chechWinStatus();
    void setHitStatusForOneSellShip(int x, int y);
    void setHitStatusForHorizontalShip(int x, int y);
    void setHitStatusForVerticalShip(int x, int y);
private:
	Cell*** board_;
	bool isGenerate_;
	const int ROWS = 10;
	const int COLUMNS = 10;
	int ships;
};

#endif // BOARD_H
