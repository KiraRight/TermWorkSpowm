#ifndef GAME_H
#define GAME_H

#include<SFML/Graphics.hpp>
#include "Menu.h"
#include"Board.h"
#include"StartGameWindow.h"
#include"Fight.h"
#include"WinMessage.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/time.h>

#define BUFLEN 30

using namespace std;
using namespace sf;

class Game
{
public:
	void menu(RenderWindow &window);
	void game(RenderWindow &window);
	void fight(RenderWindow &window, Board& board);
	void winMessage(RenderWindow &window, bool color);

	Game(int argc, char **argv);
	~Game();
private:
    int argc_;
    char **argv_;
};

#endif // GAME_H
