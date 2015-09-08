
#ifndef CLIENT_H
#define CLIENT_H

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

class Client
{
	public:
		int establishConnection();
		int sendMessage(char[]);
		int waitForEntry(string);

	private:
		int pid;
		int theSocket, n;
		struct sockaddr_in serv_addr;
		struct hostent *server;
		char buffer[256];
};
#endif
