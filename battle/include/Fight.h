#ifndef FIGHT_H
#define FIGHT_H


#include<SFML/Graphics.hpp>
#include"Board.h"

#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>

#define BUFLEN 30

using namespace sf;

class Fight
{
public:
	Fight();
	~Fight();

	void drawWindow(RenderWindow& window);
	bool gameWindowEvent(RenderWindow &window, Board &analizeBoard, int sockfd);
	void drawBoard(RenderWindow &window, Board &analizeBoard);
	void drawEnemyBoard(RenderWindow &window, Board &analizeBoard);
    void setWindowSprite(int status);    //0-no stat, 1-wait, 2 - go

private:
	Texture gameWindowTexture_;
	Sprite gameWindowSprite_;
	Texture boardTexture_;
	Sprite boardSprite_;
	Texture enemyBoardTexture_;
	Sprite enemyBoardSprite_;
	Texture missCellTexture_;
	Sprite missCellSprite_;
	Texture hitCellTexture_;
	Sprite hitCellSprite_;
	Texture shipCellTexture_;
	Sprite shipCellSprite_;
};

#endif // STARTGAMEWINDOW_H
