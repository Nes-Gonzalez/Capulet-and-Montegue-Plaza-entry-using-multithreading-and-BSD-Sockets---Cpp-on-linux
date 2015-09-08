

#include "Server.h"

#define PORTNUM 43210

using namespace std;

int Server::establishServer()
{
	mySocket = socket(AF_INET, SOCK_STREAM,0);

	if (mySocket <0)
	{
		perror("Error creating socket");
		return 1;
	}

	bzero((char *) &serv_addr, sizeof(serv_addr));

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(PORTNUM);

	if(bind(mySocket,(struct sockaddr *) &serv_addr, sizeof(serv_addr))<0)
	{
		perror("Error on binding socket");
		return 1;
	}

	listen(mySocket,5);
	client=sizeof(cli_addr);

	return 0;
}
int Server::listenForMessage()
{
		newSocket = accept(mySocket,(struct sockaddr *) &cli_addr,&client);
		if(newSocket<0)
		{
			perror("Error on accepting Client connections");
			return 1;
		}
		return newSocket;
}
int Server::readMessage(int socket)
{
	int n;
	char buffer[256];

	bzero(buffer,256);



	//reading arrival signal
	n = read(socket,buffer,255);
	if (n < 0)
	{
		perror("ERROR reading from socket");
		return 1;
	}

	else
	{
		char* charTokenizer =strtok(buffer," ");
		time=atoi(charTokenizer);

		charTokenizer = strtok(NULL," ");
		name=charTokenizer;

		charTokenizer = strtok(NULL," ");
		family=charTokenizer;
		return 0;

	}
}

int Server::sendMessage(int socket,char buffer[256])
{

	int n;

	//cout<<"server sending msg to "<<buffer<<endl;

	n=write(socket,buffer,strlen(buffer));
	if (n < 0)
    {
		perror("ERROR writing to socket");
		return 1;
    }
	return 0;
}

void Server::closeSocket(int socket)
{
	close(socket);
}

string Server::getFamily()
{
	return family;
}
string Server::getName()
{
	return name;
}
unsigned int Server::getTime()
{
	return time;
}
