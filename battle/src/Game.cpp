#include "Game.h"


void Game::menu(RenderWindow & window)
{
	Menu menu;
	menu.setMenu();
	menu.drawMenu(window);
	while (menu.getState())
	{
		window.clear();
		menu.drawMenu(window);
		window.display();
		menu.menuEvent(window);
		if (menu.getNumberButton() == 1)
		{
			game(window);
		}
	}
}

void Game::game(RenderWindow &window)
{
	StartGameWindow gameWindow;
	Board analizeBoard;

	while (window.isOpen())
	{
		gameWindow.gameWindowEvent(window, analizeBoard);
		if(gameWindow.checkReady())
		{
            fight(window, analizeBoard);
            return;
		}
		window.clear();
		gameWindow.drawWindow(window);
		gameWindow.drawBoard(window, analizeBoard);
		window.display();
	}
}

void Game::fight(RenderWindow &window, Board& board)
{
	Fight gameWindow;
	Board enemyBoard;

	int sockfd, i, check, start;
	struct sockaddr_in serv_addr;
	struct hostent *server;
	struct timeval time;

	time.tv_sec = 60;
	time.tv_usec = 0;

	fd_set read_fds;
	fd_set tmp_fds;
	int fdmax;

	FD_ZERO(&read_fds);
	FD_ZERO(&tmp_fds);

	char buffer[BUFLEN];
	if (argc_ < 3)
	{
	   fprintf(stderr,"Usage %s server_address server_port\n", argv_[0]);
	   exit(0);
	}

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
	{
		perror("ERROR opening socket");
		exit(1);
    }

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(atoi(argv_[2]));
	inet_aton(argv_[1], &serv_addr.sin_addr);

	if (connect(sockfd,(struct sockaddr*) &serv_addr,sizeof(serv_addr)) < 0)
	{
		perror("ERROR connecting");
        exit(1);
    }

	FD_SET(sockfd, &read_fds);
	fdmax = sockfd;

    gameWindow.setWindowSprite(1);
    window.clear();
    gameWindow.drawWindow(window);
    gameWindow.drawBoard(window, board);
    window.display();

    tmp_fds = read_fds;                              //ожидание сообщения к началу игры
    int trySelect;
    trySelect = select(fdmax + 1, &tmp_fds, NULL, NULL, &time);
    if (trySelect == -1)
    {
        perror("ERROR in select\n");
        exit(1);
    }
    else
        if(trySelect == 0)
        {
            close(sockfd);
            return;
        }

    memset(buffer, 0, BUFLEN);

    if (FD_ISSET(sockfd, &tmp_fds))
    {
        int check;
        if ((check = recv(sockfd, buffer, sizeof(buffer), 0)) <= 0)
        {
            if (check == 0)
            {
                perror("We haven't server!!!\n");
                exit(1);
            }
            else
            {
                perror("ERROR in recv\n");
                exit(1);
            }
            close(sockfd);
            FD_CLR(sockfd, &read_fds);
        }
        else
        {
            printf ("%s\n", buffer);
        }
    }

    start = buffer[0] - '0';                //0 или 1 - кто первый ходит

    while (window.isOpen())
	{
		if(start)
		{
            gameWindow.setWindowSprite(2);
            window.clear();
            gameWindow.drawWindow(window);
            gameWindow.drawBoard(window, board);
            gameWindow.drawEnemyBoard(window,enemyBoard);
            window.display();

            while(!gameWindow.gameWindowEvent(window, enemyBoard, sockfd)); //здесь ход

            tmp_fds = read_fds;                              //ожидание статуса ячейки
            trySelect = select(fdmax + 1, &tmp_fds, NULL, NULL, &time);
            if (trySelect == -1)
            {
                perror("ERROR in select\n");
                exit(1);
            }
            else
                if(trySelect == 0)
                {
                    close(sockfd);
                    return;
                }
            memset(buffer, 0, BUFLEN);

            if (FD_ISSET(sockfd, &tmp_fds))
            {
                int check;
                if ((check = recv(sockfd, buffer, sizeof(buffer), 0)) <= 0)
                {
                    if (check == 0)
                    {
                        perror("We haven't server!!!\n");
                        exit(1);
                    }
                    else
                    {
                        perror("ERROR in recv\n");
                        exit(1);
                    }
                }
                else
                {
                    printf ("You get %s\n", buffer);  //0-miss, 1-hit, 2-crash
                }

                if(buffer[0]=='e')
                {
                    close(sockfd);
                    return;
                }

                int status = buffer[2] - '0';
                int x = buffer[0] - '0';
                int y = buffer[1] - '0';
                enemyBoard.analize(status,x,y);
                if(status==0)
                    start=0;
                    else
                        start = 1;
                printf("start == %d\n", start);
            }
		}
		else
		{
            gameWindow.setWindowSprite(1);
            window.clear();
            gameWindow.drawWindow(window);
            gameWindow.drawBoard(window, board);
            gameWindow.drawEnemyBoard(window,enemyBoard);
            window.display();

            tmp_fds = read_fds;                              //ожидание хода
            trySelect = select(fdmax + 1, &tmp_fds, NULL, NULL, &time);
            if (trySelect == -1)
            {
                perror("ERROR in select\n");
                exit(1);
            }
            else
                if(trySelect == 0)
                {
                    close(sockfd);
                    return;
                }

            memset(buffer, 0, BUFLEN);

            if (FD_ISSET(sockfd, &tmp_fds))
            {
                int check;
                if ((check = recv(sockfd, buffer, sizeof(buffer), 0)) <= 0)
                {
                    if (check == 0)
                    {
                        perror("We haven't server!!!\n");
                        exit(1);
                    } else
                    {
                        perror("ERROR in recv\n");
                        exit(1);
                    }
                    close(sockfd);
                    FD_CLR(sockfd, &read_fds);
                }
                else
                {
                    printf ("Get hit on %s\n", buffer);
                }

                if(buffer[0]=='e')
                {
                    close(sockfd);
                    return;
                }
            }

            int x = buffer[0]- '0';
            int y = buffer[1]- '0';
            start = board.returnstatus(x,y,sockfd);
            printf("start == %d\n", start);
		}

		if(!board.chechWinStatus())
		{
            printf("close %d in win-fall, start =%d\n", sockfd,start);
            close(sockfd);
            winMessage(window,false);
            return;
		}
		else
            if(!enemyBoard.chechWinStatus())
            {
                printf("close %d in win-fall, start =%d\n", sockfd,start);
                close(sockfd);
                winMessage(window,true);
                return;
            }
    }
}

void Game::winMessage(RenderWindow &window, bool status)
{
	WinMessage message(status);
	while (message.getIsMessage())
	{
		message.events(window);
		window.clear();
		message.draw(window);
		window.display();
	}
}

Game::Game(int argc, char **argv)
{
    this->argc_=argc;
    this->argv_=argv;
}


Game::~Game()
{
}
