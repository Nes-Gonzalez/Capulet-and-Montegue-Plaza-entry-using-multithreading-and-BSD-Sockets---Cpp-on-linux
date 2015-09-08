
#ifndef SERVER_H
#define SERVER_H

#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <netdb.h>
#include <strings.h>
#include <iostream>

using namespace std;

class Server
{
	public:
		int readMessage(int);
		int sendMessage(int,char[]);
		int establishServer();
		int listenForMessage();
		string getFamily();
		string getName();
		unsigned int getTime();
		void closeSocket(int);
	private:
		int mySocket, newSocket;
		socklen_t client;
		char buffer[256];
		struct sockaddr_in serv_addr, cli_addr;
		string name;
		string family;
		unsigned int time;
};
#endif
