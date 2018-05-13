#include <time.h>
#include<SFML/Graphics.hpp>
#include"Game.h"

using namespace std;
using namespace sf;

int main(int argc, char *argv[])
{
	RenderWindow window(VideoMode(600, 400), "Battleship!");
	Game game(argc,argv);
	while (window.isOpen())
	{
		game.menu(window);
	}
	return 0;
}
