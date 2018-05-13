#include "StartGameWindow.h"



StartGameWindow::StartGameWindow()
{
	this->gameWindowTexture_.loadFromFile("images/window.png");
	this->gameWindowSprite_.setTexture(gameWindowTexture_);
	this->gameWindowSprite_.setPosition(0, 0);
	this->generateButtonTexture_.loadFromFile("images/Generate.png");
	this->generateButtonSprite_.setTexture(generateButtonTexture_);
	this->generateButtonSprite_.setPosition(320, 100);
	this->startButtonTexture_.loadFromFile("images/Start.png");
	this->startButtonSprite_.setTexture(startButtonTexture_);
	this->startButtonSprite_.setPosition(320, 220);
	this->boardTexture_.loadFromFile("images/board.png");
	this->boardSprite_.setTexture(boardTexture_);
	this->boardSprite_.setPosition(50, 100);
	this->shipCellTexture_.loadFromFile("images/ship_cell.png");
	this->shipCellSprite_.setTexture(shipCellTexture_);
	this->isReady_ = false;
}


StartGameWindow::~StartGameWindow()
{
}

void StartGameWindow::drawWindow(RenderWindow& window)
{
    //window->clear();
        window.draw(this->gameWindowSprite_);
        window.draw(this->boardSprite_);
        window.draw(this->generateButtonSprite_);
        window.draw(this->startButtonSprite_);
	//window->display();
   /* else
    {
        window.draw(this->gameWindowSprite_);
        window.draw(this->boardSprite_);
    }*/
}

void StartGameWindow::gameWindowEvent(RenderWindow &window, Board &analizeBoard)
{
	Event event;
	Vector2i pixelPos = Mouse::getPosition(window);
	Vector2f pos = window.mapPixelToCoords(pixelPos);
	while (window.pollEvent(event))
	{
		if (event.type == Event::Closed)
		{
			window.close();
		}
		if (event.type == Event::MouseButtonPressed)
			if (event.key.code == Mouse::Left)
			{
				if (this->generateButtonSprite_.getGlobalBounds().contains(pos.x, pos.y))
				{
					analizeBoard.generateBoard();
				}
				if (this->startButtonSprite_.getGlobalBounds().contains(pos.x, pos.y))
				{
					if(analizeBoard.checkBoard())
					{
                        this->isReady_ = true;
					}
				}
			}
	}
}

void StartGameWindow::drawBoard(RenderWindow & window, Board &analizeBoard)
{
	for (int y = 0; y < 10; y++)
		for (int x = 0; x < 10; x++)
		{
			if (analizeBoard.getBoard()[y][x]->checkShip())
			{
				this->shipCellSprite_.setPosition(50 + 20*x, 100 + 20*y);
				window.draw(this->shipCellSprite_);
			}
		}
}

bool StartGameWindow::checkReady()
{
	return this->isReady_;
}
