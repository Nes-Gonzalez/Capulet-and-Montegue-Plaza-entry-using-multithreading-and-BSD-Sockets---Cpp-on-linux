
#include "Server.h"
#include <vector>
#include <iterator>
#include <algorithm>

using namespace std;

int main()
{
	Server theServer;
	int socket;
	theServer.establishServer();
	vector<string> capulets;
	vector<int> capuletSocket;
	vector<string> montagues;
	vector<int> montagueSockets;
	int capuletsInPlaza=0;
	int montaguesInPlaza=0;
	int capuletsWaitingToEnter=0;
	int montaguesWaitingToEnter=0;
	char buffer[256];

	cout<<endl;
	while(true)
	{
		socket=theServer.listenForMessage();
		theServer.readMessage(socket);

		//uncomment to see who is sending msg
		//cout<<endl<<"Got message from "<<theServer.getFamily()<<" "<<theServer.getName()<<endl;

		//check message for family
		if(theServer.getFamily()=="Capulet")
		{

			//check name if already waiting
			bool tester = false;
			int i=0;
			for(i=0;i<capulets.size();i++)
			{
				if(capulets[i]==theServer.getName())
				{
					tester = true;
					break;
				}
			}

			//leave plaza message
			if(tester)
			{
				capulets.erase(capulets.begin()+i);
				//capuletSocket.erase(capuletSocket.begin()+i);
				capuletsInPlaza--;
				cout<<theServer.getFamily()<<" "<<theServer.getName()<<" leaves the plaza"<<endl;
			}
			else //arrival message
			{
				capuletsWaitingToEnter++;
				capulets.push_back(theServer.getName());
				capuletSocket.push_back(socket);
				cout<<theServer.getFamily()<<" "<<theServer.getName()<<" arrives"<<endl;
			}

		}
		else
		{
			bool tester = false;
			int i=0;
			for(i=0;i<montagues.size();i++)
			{
				if(montagues[i]==theServer.getName())
				{
					tester = true;
					break;
				}
			}
			//leave plaza message
			if(tester)
			{
				montagues.erase(montagues.begin()+i);
				//montagueSockets.erase(montagueSockets.begin()+i);
				montaguesInPlaza--;
				cout<<theServer.getFamily()<<" "<<theServer.getName()<<" leaves the plaza"<<endl;
			}
			else//arrival message
			{
				montaguesWaitingToEnter++;
				montagues.push_back(theServer.getName());
				montagueSockets.push_back(socket);
				cout<<theServer.getFamily()<<" "<<theServer.getName()<<" arrives"<<endl;
			}

		}

		if(capuletsInPlaza==0 && montaguesWaitingToEnter>0)
		{
			//cout<<"letting in MONTAGUES"<<endl;
			for(int i;i<montagues.size();i++)
			{
				montaguesWaitingToEnter--;
				montaguesInPlaza++;

				strcpy(buffer,montagues[i].c_str());

				theServer.sendMessage(montagueSockets[i],buffer);
				cout<<"Montague"<<" "<<montagues[i]<<" enters the plaza "<<endl;
			}
		}
		else if(montaguesInPlaza==0 && capuletsWaitingToEnter>0)
		{
			//cout<<"letting in Capulets"<<endl;
			for(int i;i<capulets.size();i++)
			{
				capuletsWaitingToEnter--;
				capuletsInPlaza++;

				strcpy(buffer,capulets[i].c_str());

				theServer.sendMessage(capuletSocket[i],buffer);
				cout<<"Capulet"<<" "<<capulets[i]<<" enters the plaza "<<endl;
			}

		}

		//uncomment for running counter
		//cout<<"Cap : "<<capulets.size()<<" waiting: "<<capuletsWaitingToEnter<<" In plaza: "<<capuletsInPlaza<<endl;
		//cout<<"Mont: "<<montagues.size()<<" waiting: "<<montaguesWaitingToEnter<<" In plaza: "<<montaguesInPlaza<<endl;


	}
	theServer.closeSocket(socket);
	return 0;

}
