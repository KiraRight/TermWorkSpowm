#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <vector>

#define MAX_CLIENTS	10
#define BUFLEN 30

using namespace std;

void error(char *msg)
{
	perror(msg);
	exit(1);
}

struct game
{
    int client1;
    int client2;
};

int main(int argc, char *argv[])
{
	int sockfd, newsockfd, portno;
	socklen_t clilen;
	char buffer[BUFLEN];
	struct sockaddr_in serv_addr, cli_addr;
	int check;

	struct game gameStat;

	vector<struct game> games;
	gameStat.client1 = 0;
	gameStat.client2 = 0;

	fd_set read_fds;
	fd_set tmp_fds;
	int fdmax;

	if (argc < 2)
	{
		fprintf(stderr,"Usage : %s port\n", argv[0]);
		exit(1);
	}

	FD_ZERO(&read_fds);
	FD_ZERO(&tmp_fds);

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
		error("ERROR opening socket");

	portno = atoi(argv[1]);

	memset((char *) &serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);

	if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(struct sockaddr)) < 0)
		error("ERROR on binding");

	listen(sockfd, MAX_CLIENTS);

	FD_SET(sockfd, &read_fds);
	fdmax = sockfd;

	while (1)
	{
		tmp_fds = read_fds;
		if (select(fdmax + 1, &tmp_fds, NULL, NULL, NULL) == -1)
			perror("ERROR in select");

		for(int i = 0; i <= fdmax; i++)
		{
			if (FD_ISSET(i, &tmp_fds))
			{
				if (i == sockfd)
				{
					clilen = sizeof(cli_addr);
					if ((newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen)) == -1)
						perror("ERROR in accept");
					else
					{
						FD_SET(newsockfd, &read_fds);

						if (newsockfd > fdmax)
						{
							fdmax = newsockfd;
						}

                        if(!gameStat.client1)
                            gameStat.client1 = newsockfd;
                        else
                        {
                            gameStat.client2 = newsockfd;
                            games.push_back(gameStat);
                            gameStat.client1 = 0;
                            gameStat.client2 = 0;

                            check = send(games[games.size()-1].client1, "1\0", BUFLEN, 0);
                            if (check == -1)
                            {
                                perror("Error sending message1!\n");
                            }
                            else
                                printf("We send status of start = 1 for %d\n",games[games.size()-1].client1);

                            check = send(games[games.size()-1].client2, "0\0", BUFLEN, 0);
                            if (check == -1)
                            {
                                perror("Error sending message!\n");
                            }
                            else
                                printf("We send status of start = 0 for %d\n",games[games.size()-1].client2);
                        }

                        printf("Number of games %d\n", games.size());
                        printf("New client %d connecting to server!\n", newsockfd);
                    }
                }
				else
				{
					memset(buffer, 0, BUFLEN);
					if ((check = recv(i, buffer, sizeof(buffer), 0)) <= 0)
					{
						if (check == 0)
						{
							printf("Good bue %d\n", i);

                            for (unsigned int j = 0; j < games.size(); j++)
                            {
                                if(games[j].client1==i || games[j].client2==i)
                                {
                                    if(games[j].client1==i)
                                    {
                                        FD_CLR(games[j].client1, &read_fds);

                                        check = send(games[j].client2, "e\0", BUFLEN, 0);
                                        if (check == -1)
                                        {
                                            perror("Error sending message!\n");
                                        }
                                        else
                                            printf("We send client message e for %d\n", games[j].client2);

                                        games[j].client1=0;
                                    }
                                    else
                                    {
                                        FD_CLR(games[j].client2, &read_fds);

                                        check = send(games[j].client1, "e\0", BUFLEN, 0);
                                        if (check == -1)
                                        {
                                            perror("Error sending message!\n");
                                        }
                                        else
                                            printf("We send client message e for %d\n", games[j].client2);

                                        games[j].client2=0;
                                    }
                                    if(games[j].client1&&games[j].client2)
                                        games.erase(games.begin()+j);
                                }
                            }

                            if(gameStat.client1==i)
                            {
                                FD_CLR(gameStat.client1, &read_fds);
                                gameStat.client1=0;
                            }
                        }
                        else
                        {
                            printf("problem in %d\n", i);
                            perror("ERROR in recv");
                        }
                        close(i);
                    }
                    else
                    {
                        for (unsigned int j = 0; j < games.size(); j++)
                        {
                            if(games[j].client1==i || games[j].client2==i)
                            {
                                if(games[j].client1==i)
                                {
                                    check = send(games[j].client2, buffer, BUFLEN, 0);
                                    if (check == -1)
                                    {
                                        perror("Error sending message!\n");
                                    }
                                    else
                                        printf("We send client message %s for %d\n",buffer,games[j].client2);
                                }
                                else
                                {
                                    check = send(games[j].client1, buffer, BUFLEN, 0);
                                    if (check == -1)
                                    {
                                        perror("Error sending message!\n");
                                    }
                                    else
                                        printf("We send client message %s for %d\n",buffer,games[j].client1);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    close(sockfd);
    return 0;
}
