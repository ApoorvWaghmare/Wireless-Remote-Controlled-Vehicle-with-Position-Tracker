#include <ctime>
#include <iostream>
#include <chrono>

#include "Bot.h"

using namespace std;

Bot::Bot()
{
    //ctor
}

void Bot::initializeAllSystems()
{
    server.createSocket();
    botController.setUpIOPins();
    accTime.MPUInitialization();
}

void Bot::acceptClient()
{
    server.acceptClient();
}

void Bot::startOperations()
{
    int direction;

    chrono::steady_clock::time_point start = chrono::steady_clock::now();

	while(1)
	{
		int tempVal = server.getClientData();

		if(server.getRecievedBytes() == 0)
			cout<<"Connection failed from client side"<<endl;
		else if(server.getRecievedBytes() < -1)
			continue;
		else if(server.getRecievedBytes() > 0)
		{
            if(tempVal == 6)
                break;

            direction = tempVal;
		}

		botController.runBot(direction);

		cout << "direction = " << direction << endl;

		if(direction != 5)
            positionComputer.computeCoordinates(&accTime, &xAxis, &yAxis, start);

		server.sendData(xAxis.getCoordinate());
        server.sendData(yAxis.getCoordinate());
	}
}

Bot::~Bot()
{
    //dtor
}
