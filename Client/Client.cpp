
#include "Client.h"

#define PORTNUM 43210

using namespace std;

int Client::establishConnection()
{

	theSocket = socket(AF_INET,SOCK_STREAM,0);


	if(theSocket<0)
	{
		perror("Error opening socket");
		return 1;
	}

	const char* hostname = "bayou.cs.uh.edu";
	server = gethostbyname(hostname);

	if(server==NULL)
	{
		perror("Error finding server");
		return 1;
	}

	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
	serv_addr.sin_port = htons(PORTNUM);

	if(connect(theSocket,(struct sockaddr*)&serv_addr, sizeof(serv_addr))<0)
	{
		perror("Error connecting");
		return 1;
	}
}

int Client::sendMessage(char buffer[256])
{

	n = write(theSocket,buffer,strlen(buffer));

	if(n<0)
	{
		perror("Error writing to server");
		return 1;
	}

	return 0;

}
int Client::waitForEntry(string name)
{
	string tempName;
	while(tempName != name)
	{
		bzero(buffer,256);
		tempName="";
		n = read(theSocket, buffer, 255);
		if (n < 0)
		{
			perror("ERROR reading from socket");
			return 1;
		}

		char* charTokenizer =strtok(buffer," ");
		tempName=charTokenizer;

		//cout<<"loop for: "<<tempName<<" == "<<name<<endl;
	}
	return 0;
}
