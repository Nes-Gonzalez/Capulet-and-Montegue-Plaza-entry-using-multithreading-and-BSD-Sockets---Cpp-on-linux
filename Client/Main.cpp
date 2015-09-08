
#include "Client.h"
#include <sstream>

using namespace std;

int main()
{

	Client theClient;


	int pid;
	string family;
	string name;
	unsigned int arrivalTime;
	unsigned int timeSpent;
	string wholeLine;
	char bufferOne[256];
	char bufferTwo[256];

	cout<<endl;
	while(cin>>family)
	{
		cin>>name;
		cin>>arrivalTime;
		cin>>timeSpent;

		stringstream converter;
		converter<<arrivalTime<<" "<<name<<" "<<family;
		wholeLine=converter.str();
		strcpy(bufferOne,wholeLine.c_str());

		converter.str("");
		converter<<timeSpent<<" "<<name<<" "<<family;
		wholeLine=converter.str();
		strcpy(bufferTwo,wholeLine.c_str());

		pid=fork();
		if(pid==0)
		{
			if(theClient.establishConnection()==1)
			{
				cout<<"Establishing Connection failed, exiting..."<<endl;
				return 0;
			}


			cout<<"I am "<<family<<" "<<name<<" waiting for "<<arrivalTime<<endl;

			sleep(arrivalTime);

			cout<<"I am "<<family<<" "<<name<<" requesting entry "<<endl;
			//sends arrival notification
			if(theClient.sendMessage(bufferOne)==1)
			{
				cout<<"Sending Message failed, exiting..."<<endl;
				return 0;
			}


			//waits for permission to enter
			if(theClient.waitForEntry(name)==1)
			{
				cout<<"Receive entry signal failed, exiting..."<<endl;
				return 0;
			}

			cout<<"I am "<<family<<" "<<name<<" allowed entry "<<endl;
			//enters hangs around plaza till they leave
			sleep(timeSpent);


			if(theClient.establishConnection()==1)
			{
				cout<<"Establishing Connection failed, exiting..."<<endl;
				return 0;
			}

			cout<<"I am "<<family<<" "<<name<<" and am leaving "<<endl;
			//leaving plaza
			if(theClient.sendMessage(bufferTwo)==1)
			{
				cout<<"Sending Message failed, exiting..."<<endl;
				return 0;
			}

			return 0;
		}
	}
	//parent waiting
	while(wait(0)!=-1);
	cout<<"All Capulets and Montagues have visited the plaza"<<endl<<endl;

	return 0;
}
