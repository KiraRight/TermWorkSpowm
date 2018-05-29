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
    this->ships =10;
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

void Board::analize(int status,int x, int y)
{
    int horizontal = 2;// 1-horizontal,0-ver,2 -onecell
    if(status)
        this->board_[y][x]->setShip();
    if(status==1)
    {
        this->ships--;
        while((y+1) < ROWS && this->board_[y+1][x]->checkShip())
        {
            horizontal = 0;
            y++;
        }
        if(horizontal==2)
            if((y-1)>=0 && this->board_[y-1][x]->checkShip())
                horizontal=0;
        if(horizontal==2)
            while((x+1) < COLUMNS && this->board_[y][x + 1]->checkShip())
            {
                horizontal = 1;
                x++;
            }
        if(horizontal==2)
            if((x-1)>=0 && this->board_[y][x-1]->checkShip())
                horizontal=1;
        if(horizontal==2)
        {
            setHitStatusForOneSellShip(x, y);
        }
        else
            if(horizontal==1)
            {
                setHitStatusForHorizontalShip(x, y);
            }
            else
            {
                setHitStatusForVerticalShip(x, y);
            }
    }
    else
        this->board_[y][x]->setWalked();
}

void Board::setHitStatusForOneSellShip(int x, int y)
{
    if((y+1) < ROWS)
    {
        this->board_[y+1][x]->setWalked();
        if((x+1) < COLUMNS)
            this->board_[y+1][x+1]->setWalked();
    }
    if((x+1)<COLUMNS)
    {
        this->board_[y][x+1]->setWalked();
        if((y-1) >=0)
            this->board_[y-1][x+1]->setWalked();
    }
    if((y-1)>=0)
    {
        this->board_[y-1][x]->setWalked();
        if((x-1) >=0)
            this->board_[y-1][x -1]->setWalked();
    }
    if((x-1)>=0)
    {
        this->board_[y][x-1]->setWalked();
        if((y+1) < ROWS)
            this->board_[y+1][x-1]->setWalked();
    }
}

void Board::setHitStatusForHorizontalShip(int x, int y)
{
    if((x+1)<COLUMNS)
    {
        this->board_[y][x+1]->setWalked();
        if((y-1)>=0)
        {
            this->board_[y-1][x+1]->setWalked();
            while(x>=0&&this->board_[y][x]->checkShip())
            {
                this->board_[y-1][x]->setWalked();
                x--;
            }
        }
        else
            for(;x>=0&&this->board_[y][x]->checkShip();x--);
                if(x>=0)
                {
                    if((y-1)>=0)
                        this->board_[y-1][x]->setWalked();
                    this->board_[y][x]->setWalked();
                    if((y+1)<ROWS)
                        this->board_[y+1][x]->setWalked();
                }
                if((y+1)<ROWS)
                {
                    x++;
                    while(x<ROWS&&this->board_[y][x]->checkShip())
                    {
                        this->board_[y+1][x]->setWalked();
                        x++;
                    }
                    if(x<COLUMNS)
                        this->board_[y+1][x]->setWalked();
                }
    }
    else
    {
        if((y-1)>=0)
        {
            while(x>=0&&this->board_[y][x]->checkShip())
            {
                this->board_[y-1][x]->setWalked();
                x--;
            }
        }
        else
            for(;x>=0&&this->board_[y][x]->checkShip();x--);
            if(x>=0)
            {
                if((y-1)>=0)
                    this->board_[y-1][x]->setWalked();
                this->board_[y][x]->setWalked();
            }
            if((y+1)<ROWS)
            {
                if(x>=0)
                    this->board_[y+1][x]->setWalked();
                x++;
                while(x<ROWS&&this->board_[y][x]->checkShip())
                {
                    this->board_[y+1][x]->setWalked();
                    x++;
                }
            }
    }
}
void Board::setHitStatusForVerticalShip(int x, int y)
{
    if((y+1)<ROWS)
    {
        this->board_[y+1][x]->setWalked();
        if((x-1)>=0)
        {
            this->board_[y+1][x-1]->setWalked();
            while(y>=0&&this->board_[y][x]->checkShip())
            {
                this->board_[y][x-1]->setWalked();
                y--;
            }
            if(y>=0)
                this->board_[y][x-1]->setWalked();
        }
        else
            for(;y>=0&&this->board_[y][x]->checkShip();y--);
            if(y>=0)
            {
                this->board_[y][x]->setWalked();
            }
            if((x+1)<COLUMNS)
            {
                if(y>=0)
                    this->board_[y][x+1]->setWalked();
                y++;
                while(y<COLUMNS&&this->board_[y][x]->checkShip())
                {
                    this->board_[y][x+1]->setWalked();
                    y++;
                }
                if(y<COLUMNS)
                    this->board_[y][x+1]->setWalked();
            }
        }
        else
        {
            if((x-1)>=0)
            {
                while(y>=0&&this->board_[y][x]->checkShip())
                {
                    this->board_[y][x-1]->setWalked();
                    y--;
                }
                if(y>=0)
                    this->board_[y][x-1]->setWalked();
            }
            else
                for(;y>=0&&this->board_[y][x]->checkShip();y--);
                if(y>=0)
                {
                    this->board_[y][x]->setWalked();
                }
                if((x+1)<COLUMNS)
                {
                    if(y>=0)
                        this->board_[y][x+1]->setWalked();
                    y++;
                    while(y<ROWS&&this->board_[y][x]->checkShip())
                    {
                        this->board_[y][x+1]->setWalked();
                        y++;
                    }
                }
        }
}

int Board::returnstatus(int x,int y, int sockfd)
{
    int start = 0;
    char buffer[30];
    char cx = x|0x30;
    char cy = y|0x30;
    memset(buffer, 0, BUFLEN);
    buffer[0]=cx;
    buffer[1]=cy;
    this->board_[y][x]->setWalked();
    if(!this->board_[y][x]->checkShip())
    {
        buffer[2]='0';
        start = 1;
    }
        else
            if(checkHit(x,y))
                buffer[2]='1';
                else
                    buffer[2]='2';
    buffer[3]='\0';
    printf("Status! %s\n", buffer);
    int check = send(sockfd, buffer, BUFLEN, 0);
    if (check == -1)
    {
        perror("Error sending message!\n");
        exit(1);
    }
    return start;
}

bool Board::checkHit(int x, int y)
{
    int saveX = x;
    int saveY =y;
    this->board_[y][x]->setWalked();
    while(x<COLUMNS&&this->board_[y][x]->checkShip())
    {
        if(!this->board_[y][x]->getWalked())
            return false;
        x++;
    }
    x=saveX;
    while(x>=0&&this->board_[y][x]->checkShip())
    {
        if(!this->board_[y][x]->getWalked())
            return false;
        x--;
    }
    x=saveX;
    while(y<ROWS&&this->board_[y][x]->checkShip())
    {
        if(!this->board_[y][x]->getWalked())
            return false;
        y++;
    }
    y=saveY;
    while(y>=0&&this->board_[y][x]->checkShip())
    {
        if(!this->board_[y][x]->getWalked())
            return false;
        y--;
    }
    y=saveY;
    this->analize(1,x,y);
    return true;
}

int Board::chechWinStatus()
{
    return this->ships;
}
