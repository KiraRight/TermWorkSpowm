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

	/*Player player1(true), player2(false);
	vector<Player> players;
	players.push_back(player1);
	players.push_back(player2);
	int n = 0;
	analizBoard.analize(players[n].getColor());
	checkers.loadPosition(analizBoard.getBoard());*/
	while (window.isOpen())
	{
		gameWindow.gameWindowEvent(window, analizeBoard);
		if(gameWindow.checkReady())
		{
            fight(window, analizeBoard);
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

	int sockfd, i;
	struct sockaddr_in serv_addr;
	struct hostent *server;

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

	FD_SET(0, &read_fds);
	FD_SET(sockfd, &read_fds);
	fdmax = sockfd;

	 //gameWindow.gameWindowEvent(window, board, buffer);
        gameWindow.gameWindowEvent(window, board);
        window.clear();
		gameWindow.drawWindow(window);
		gameWindow.drawBoard(window, board);
		gameWindow.drawEnemyBoard(window,enemyBoard);
		window.display();

    while (1)
	{
        gameWindow.gameWindowEvent(window, enemyBoard);
        window.clear();
		gameWindow.drawWindow(window);
		gameWindow.drawBoard(window, board);
		gameWindow.drawEnemyBoard(window,enemyBoard);
		window.display();
		}
        /*tmp_fds = read_fds;
		if (select(fdmax + 1, &tmp_fds, NULL, NULL, NULL) == -1)
		{
			perror("ERROR in select\n");
			exit(1);
		}

		memset(buffer, 0, BUFLEN);
		if (FD_ISSET(0, &tmp_fds))
		{
			fgets(buffer, BUFLEN-1, stdin);
			buffer[strlen(buffer) - 1] = '\0';
			if (strcmp(buffer, "exit") == 0)
			{
				close(sockfd);
				return;
			}

			int check = send(sockfd, buffer, BUFLEN, 0);
			if (check == -1)
			{
				perror("Error sending message!\n");
				exit(1);
			}
		}

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
				printf ("%s\n", buffer);
			}
		}
		//gameWindow.gameWindowEvent(window, board, buffer);
	}*/


	/*while (window.isOpen())
	{

        //gameWindow.gameWindowEvent(window, board, buffer);
        gameWindow.gameWindowEvent(window, board, buffer);
        window.clear();
		gameWindow.drawWindow(window);
		gameWindow.drawBoard(window, board);
		gameWindow.drawEnemyBoard(window,enemyBoard);
		window.display();

        tmp_fds = read_fds;
		if (select(fdmax + 1, &tmp_fds, NULL, NULL, NULL) == -1)
		{
			perror("ERROR in select\n");
			exit(1);
		}
		//else
           // printf("Select\n");
		memset(buffer, 0, BUFLEN);
		if (FD_ISSET(0, &tmp_fds))
		{
			//fgets(buffer, BUFLEN-1, stdin);
			/*buffer[strlen(buffer) - 1] = '\0';
			if (strcmp(buffer, "exit") == 0)
			{
				close(sockfd);
				return;
			}
			int check = send(sockfd, buffer, BUFLEN, 0);
			if (check == -1)
			{
				perror("Error sending message!\n");
				exit(1);
			}
			else
                printf("We send message\n");
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
				printf ("%s\n", buffer);
			}
		}
		//gameWindow.gameWindowEvent(window, board, buffer);
	}*/
}

/*void Game::winMessage(RenderWindow &window, bool color)
{
	WinMessage message(color);
	while (message.getIsMessage())
	{
		message.events(window);
		window.clear();
		message.draw(window);
		window.display();
	}
	//if(window.isOpen())
	//	menu(window);
}*/

Game::Game(int argc, char **argv)
{
    this->argc_=argc;
    this->argv_=argv;
}


Game::~Game()
{
}
