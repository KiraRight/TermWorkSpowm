#include "Board.h"



Board::Board()
{
	board_ = new Cell**[ROWS];
	for (int i = 0; i < ROWS; i++)
	{
		board_[i] = new Cell*[COLUMNS];
	}
	for (int y = 0; y < ROWS; y++)
		for (int x = 0; x < COLUMNS; x++)
		{
			this->board_[y][x] = new Cell(x, y);
		}
    this->isGenerate_ = false;
}


Board::~Board()
{
}

void Board::generateBoard()
{
	for (int y = 0; y < ROWS; y++)
		for (int x = 0; x < COLUMNS; x++)
		{
			this->board_[y][x]->clean();
		}
	generateShip(4);
	generateShip(3);
	generateShip(3);
	generateShip(2);
	generateShip(2);
	generateShip(2);
	generateShip(1);
	generateShip(1);
	generateShip(1);
	generateShip(1);
}

void Board::generateShip(int nShip)
{
	srand(time(0));
	int x, y;
	int horizontal;
	bool isSet = false;
	while (!isSet)                                   //check
	{
		horizontal = rand() % (3 - 1);
		x = rand() % (COLUMNS - 1);
		y = rand() % (ROWS - 1);
		if(!horizontal)
		{
			isSet = true;
			if ((y + nShip - 1) < ROWS && !this->board_[y][x]->getBusyness())
			{
				for (int i = y; i < y + nShip; i++)
				{
					if (this->board_[i][x]->getBusyness())
					{
						isSet = false;
						break;
					}
				}
			}
			else
				isSet = false;
		}
		else
		{
			isSet = true;
			if ((x + nShip - 1) < COLUMNS && !this->board_[y][x]->getBusyness())
			{
				for (int i = x; i < x + nShip; i++)
				{
					if (this->board_[y][i]->getBusyness())
					{
						isSet = false;
						break;
					}
				}
			}
			else
				isSet = false;
		}
	}
	if (!horizontal)
	{
		if (y - 1 >= 0)
		{
			this->board_[y - 1][x]->setBusy();
			if (x - 1 >= 0)
				this->board_[y - 1][x - 1]->setBusy();
			if (x + 1 < COLUMNS)
				this->board_[y - 1][x + 1]->setBusy();
		}
		for (int i = y; i < y + nShip; i++)
		{
			this->board_[i][x]->setShip();
			if (x - 1 >= 0)
				this->board_[i][x - 1]->setBusy();
			if (x + 1 < COLUMNS)
				this->board_[i][x + 1]->setBusy();
		}
		if (y + nShip < ROWS)
		{
			this->board_[y + nShip][x]->setBusy();
			if (x - 1 >= 0)
				this->board_[y + nShip][x - 1]->setBusy();
			if (x + 1 < COLUMNS)
				this->board_[y + nShip][x + 1]->setBusy();
		}
	}
	else
	{
		if (x - 1 >= 0)
		{
			this->board_[y][x - 1]->setBusy();
			if (y - 1 >= 0)
				this->board_[y - 1][x - 1]->setBusy();
			if (y + 1 < ROWS)
				this->board_[y + 1][x - 1]->setBusy();
		}
		for (int i = x; i < x + nShip; i++)
		{
			this->board_[y][i]->setShip();
			if (y - 1 >= 0)
				this->board_[y - 1][i]->setBusy();
			if (y + 1 < ROWS)
				this->board_[y + 1][i]->setBusy();
		}
		if (x + nShip < COLUMNS)
		{
			this->board_[y][x + nShip]->setBusy();
			if (y - 1 >= 0)
				this->board_[y - 1][x + nShip]->setBusy();
			if (y + 1 < ROWS)
				this->board_[y + 1][x + nShip]->setBusy();
		}
	}
	this->isGenerate_ = true;
}

Cell *** Board::getBoard()
{
	return this->board_;
}

bool Board::checkBoard()
{
    return this->isGenerate_;
}
