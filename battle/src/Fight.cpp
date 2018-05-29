#include "Fight.h"

Fight::Fight()
{
	this->gameWindowTexture_.loadFromFile("images/window.png");
	this->gameWindowSprite_.setTexture(gameWindowTexture_);
	this->gameWindowSprite_.setPosition(0, 0);

	this->boardTexture_.loadFromFile("images/board.png");
	this->boardSprite_.setTexture(boardTexture_);
	this->boardSprite_.setPosition(50, 100);

	this->enemyBoardTexture_.loadFromFile("images/board.png");
	this->enemyBoardSprite_.setTexture(enemyBoardTexture_);
	this->enemyBoardSprite_.setPosition(350, 100);

	this->shipCellTexture_.loadFromFile("images/ship_cell.png");
	this->shipCellSprite_.setTexture(shipCellTexture_);
	this->hitCellTexture_.loadFromFile("images/hit_cell.png");
	this->hitCellSprite_.setTexture(hitCellTexture_);
	this->missCellTexture_.loadFromFile("images/miss_cell.png");
	this->missCellSprite_.setTexture(missCellTexture_);
}


Fight::~Fight()
{
}

void Fight::drawWindow(RenderWindow& window)
{
        window.draw(this->gameWindowSprite_);
        window.draw(this->boardSprite_);
        window.draw(this->enemyBoardSprite_);
}

bool Fight::gameWindowEvent(RenderWindow &window, Board &analizeBoard, int sockfd)
{
	Event event;
	Vector2i pixelPos = Mouse::getPosition(window);
	Vector2f pos = window.mapPixelToCoords(pixelPos);
	char buffer[30];
	while (window.pollEvent(event))
	{
		if (event.type == Event::MouseButtonPressed)
			if (event.key.code == Mouse::Left)
			{
                if (this->enemyBoardSprite_.getGlobalBounds().contains(pos.x, pos.y))
				{
                    memset(buffer, 0, BUFLEN);
                    int x, y;
                    x = (pos.x - 350)/20;
                    y = (pos.y - 100)/20;
                    if(analizeBoard.getBoard()[y][x]->getWalked())
                        return false;
					buffer[0] = x|0x30;
					buffer[1] = y|0x30;
					buffer[2] = '\0';
					analizeBoard.getBoard()[y][x]->setWalked();
					printf("Attak! %s\n",buffer);
					int check = send(sockfd, buffer, BUFLEN, 0);
                    if (check == -1)
                    {
                        perror("Error sending message!\n");
                        exit(1);
                    }
					return true;
				}
			}
	}
}

void Fight::drawBoard(RenderWindow & window, Board &analizeBoard)
{
	for (int y = 0; y < 10; y++)
		for (int x = 0; x < 10; x++)

            if(analizeBoard.getBoard()[y][x]->getWalked())
            {
                if (analizeBoard.getBoard()[y][x]->checkShip())
                {
                    this->hitCellSprite_.setPosition(50 + 20*x, 100 + 20*y);
                    window.draw(this->hitCellSprite_);
                }
                else
                {
                    this->missCellSprite_.setPosition(50 + 20*x, 100 + 20*y);
                    window.draw(this->missCellSprite_);
                }
            }
            else
                if (analizeBoard.getBoard()[y][x]->checkShip())
                {
                    this->shipCellSprite_.setPosition(50 + 20*x, 100 + 20*y);
                    window.draw(this->shipCellSprite_);
                }
}

void Fight::drawEnemyBoard(RenderWindow & window, Board &analizeBoard)
{
	for (int y = 0; y < 10; y++)
		for (int x = 0; x < 10; x++)
		{
			if (analizeBoard.getBoard()[y][x]->getWalked())
			{
                if (analizeBoard.getBoard()[y][x]->checkShip())
                {
                    this->hitCellSprite_.setPosition(350 + 20*x, 100 + 20*y);
                    window.draw(this->hitCellSprite_);
                }
                else
                {
                    this->missCellSprite_.setPosition(350 + 20*x, 100 + 20*y);
                    window.draw(this->missCellSprite_);
                }
			}
		}
}

void Fight::setWindowSprite(int status)    //0-no stat, 1-wait, 2 - go
{
    if(!status)
    {
        this->gameWindowTexture_.loadFromFile("images/window.png");
        this->gameWindowSprite_.setTexture(gameWindowTexture_);
    }
    else
        if(status==1)
        {
            this->gameWindowTexture_.loadFromFile("images/window_wait.png");
            this->gameWindowSprite_.setTexture(gameWindowTexture_);
        }
        else
            {
                this->gameWindowTexture_.loadFromFile("images/window_go.png");
                this->gameWindowSprite_.setTexture(gameWindowTexture_);
            }
}
