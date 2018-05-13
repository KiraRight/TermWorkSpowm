#ifndef FIGHT_H
#define FIGHT_H


#include<SFML/Graphics.hpp>
#include"Board.h"

#include<cstring>

using namespace sf;

class Fight
{
public:
	Fight();
	~Fight();

	void drawWindow(RenderWindow& window);
	void gameWindowEvent(RenderWindow &window, Board &analizeBoard);
	void drawBoard(RenderWindow &window, Board &analizeBoard);
	void drawEnemyBoard(RenderWindow &window, Board &analizeBoard);

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
