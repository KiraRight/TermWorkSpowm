#ifndef STARTGAMEWINDOW_H
#define STARTGAMEWINDOW_H


#include<SFML/Graphics.hpp>
#include"Board.h"

using namespace sf;

class StartGameWindow
{
public:
	StartGameWindow();
	~StartGameWindow();

	void drawWindow(RenderWindow& window);
	void gameWindowEvent(RenderWindow &window, Board &analizeBoard);
	void drawBoard(RenderWindow &window, Board &analizeBoard);
	bool checkReady();

private:
    bool isReady_;
	Texture gameWindowTexture_;
	Sprite gameWindowSprite_;
	Texture boardTexture_;
	Sprite boardSprite_;
	Texture generateButtonTexture_;
	Sprite generateButtonSprite_;
	Texture startButtonTexture_;
	Sprite startButtonSprite_;
	Texture shipCellTexture_;
	Sprite shipCellSprite_;
};

#endif // STARTGAMEWINDOW_H
